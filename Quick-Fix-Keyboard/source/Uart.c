/*
 * Uart.c
 *
 *  Created on: Nov 1, 2020
 *      Author: maitr
 *       *      Parts of the code was inspired from Alexander .G Dean
 *      https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 */

#include "UART.h"
#include <stdio.h>

#include "MKL25Z4.h"
#include "core_cm0plus.h"
cb_t TxQ, RxQ;
/********************************************************************************************************
 * void UART_init(uint32_t baud):This function initalizes Uart
 * @param baud rate: takes input baud rate, the baud rate at which the UART needs to initialize
 * @returns void
 * @credit Some of the code was inspired from Dean's code
 * Baud rate for Uart is calculated by the formula:
 * Baud rate = Baud Rate = Baud Clock / ((OSR+1) * BR)
 * where OSR is Sampling rate we have used OSR=15
 * Baud clock as 24Mhz
 * BR : is calculated depending on baud rate and is stored in BDL and BDH
 ***********************************************************************************************************/

void UART_init(uint32_t baud)
{

	uint16_t select_baud;

	// Enable PORTA clock
	SIM->SCGC5 |= SIM_SCGC5_PORTA(1);

	PORTA->PCR[1] |=  PORT_PCR_MUX(2); /* PTA1 as ALT2 (UART0)Rx */
	PORTA->PCR[2]|=  PORT_PCR_MUX(2); /* PTA2 as ALT2 (UART0)Tx */

	// Select FLLCLK as UART0 clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Enable UART0 Clock
	SIM->SCGC4 |= SIM_SCGC4_UART0(1);

	// Configure Baud Rate as

	// Set baud rate and oversampling ratio
	select_baud = (uint16_t)((SYS_CLOCK)/(baud * UART_SAMPLERATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(select_baud>>8);
	UART0->BDL = UART0_BDL_SBR(select_baud);
	UART0->C4 |= UART0_C4_OSR(UART_SAMPLERATE-1);

	// select  stop bit
	UART0->BDH |=  UART0_BDH_SBNS(STOP_BITS);

	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
										| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);


	// Configure Serial Port as 8-N-2
	// (8 data bits, No parity and 2 stop bit)for our system can be changed by changing defines
	UART0->C1  |=(((PARITY<<3)|(BITS<<1))&0xFFFFFFFF);




	// Configure Transmitter/Receiever
	UART0->C2  |= UART_C2_TE(1);  // Tx Enabled
	UART0->C2  |= UART_C2_RE(1);  // Rx Enabled

	// Enable UART0 Interrupt
	cb_init(&TxQ);  // create buffer Tx
	cb_init(&RxQ);	//create buffer Rx


	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);//enable uart

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);



}
/********************************************************************************************************
 * int __sys_write(int handle, char *buf, int size):Function ti tie printf to UART
 * @param handle:Writes the specified bytes to either stdout (handle = 1) or stderr (handle = 2).
 * @param char* buf: accepts input character pointer for string to be printed
 * @param int size: takes input of type int which specifies size
 * @returns returns 0 on success
 *
 * enqueues the characters from string byte by byte so that the flow of enqueue and transmitting to UART is controlled
 ************************************************************************************************************************/

int __sys_write(int handle, char *buf, int size)
{

	(void)handle;//do nothing for our implementation
	//if string is empty return -1
	if(buf == NULL) {
		return -1;
	}
	while(cb_Full(&TxQ)) {
					; // Wait for the space to openup
				}
	while (size) { // copy characters

		size_t amt =cb_Enqueue(&TxQ, buf,size); // this code is referred from Prof. Howdy Pierce's lecture
		size-= amt;
		buf += amt;
	}

	if(!(UART0->C2 & UART0_C2_TIE_MASK)) //start transmitter if it isnt already started
	{
		UART0->C2 |= UART0_C2_TIE(1);
	}

	return 0;
}
/********************************************************************************************************
 * int __sys_readc():Function to tie getchar to UART

 * @returns returns character dequeued on success
 *
 * dequeues the character from receiver buffer when its received on UART
 ************************************************************************************************************************/


int __sys_readc()
{
	char ch;
	if (cb_Dequeue(&RxQ, &ch, 1) != 1)//check if 1 byte is dequeued from receiver buffer
	{
		return -1;
	}
	return ch;//return character
}

/********************************************************************************************************
void UART0_IRQHandler(void):Interrupt handler to handle Uart Interrupt
When recieved a character and when rx interrupt is enabled  enqueue character  to RX buffer
When transmitter interrupt is enabled dequeue a character from Tx buffer to the UART
 ************************************************************************************************************************/

void UART0_IRQHandler(void) {
	uint8_t ch;

	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
			UART_S1_FE_MASK | UART_S1_PF_MASK)) {
		// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
				UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		// read the data register to clear RDRF
		ch = UART0->D;
	}
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// received a character
		ch = UART0->D;
		cb_Enqueue(&RxQ, &ch , sizeof(ch));//enqueue the character to receiver buffer

	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
		// can send another character
		if(cb_Dequeue(&TxQ, &ch, 1)) //dequeue one character from Tx buffer to UARt
		{
			UART0->D = ch;
		} else {
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}

	}
}




