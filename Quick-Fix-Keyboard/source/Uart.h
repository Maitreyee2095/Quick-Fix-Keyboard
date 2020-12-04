/*
 * Uart.h
 *
 *  Created on: Nov 1, 2020
 *      Author: maitreye Rao
 *
 *      Parts of the code was inspired from Alexander .G Dean
 *      https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "core_cm0plus.h"
#include <stdio.h>
#include "Circular_buffer.h"
#ifndef UART_H_
#define UART_H_

/*****************************************DEFINES*****************************************************************/

#define UART_SAMPLERATE 	(16) //Define Uart_samplerate
#define BUS_CLOCK 			(24e6)
#define SYS_CLOCK			(24e6) //define sysclock as 24Mhz
#define PARITY      (0)//Parity none
#define BITS        (0)//0 for 8 bit, 1 for 9 bit
#define STOP_BITS   (1)//1 for 2 stop bits , 0 for 1 stop bit

/********************************************************************************************************
 * void UART_init(uint32_t baud):This function initalizes Uart
 * @param baud rate: takes input baud rate, the baud rate at which the UART needs to initialize
 * @returns void
 *
 * Baud rate for Uart is calculated by the formula:
 * Baud rate = Baud Rate = Baud Clock / ((OSR+1) * BR)
 * where OSR is Sampling rate we have used OSR=15
 * Baud clock as 24Mhz
 * BR : is calculated depending on baud rate and is stored in BDL and BDH
 ***********************************************************************************************************/
void UART_init(uint32_t baud);


extern cb_t TxQ, RxQ;

#endif /* UART_H_ */
