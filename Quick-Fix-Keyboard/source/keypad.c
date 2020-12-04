/*
 * keypad.c
 *
 *  Created on: Nov 26, 2020
 *      Author: maitreyee rao
 *      In this file you will find function to scan a matrix key pad to detect a pressed keys
 *
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "keypad.h"
#include "analog_out.h"



/**************************************************
DEFINES
 ***************************************************/

#define ROW1  ((uint32_t)1 << 8)  // PTB8
#define ROW2  ((uint32_t)1 << 9)  // PTB9


#define COL1   ((uint32_t)1 << 2)  // PTE2
#define COL2  ((uint32_t)1 << 3)  // PTE3
#define COL3   ((uint32_t)1 << 4)  // PTE4
#define COL4	 ((uint32_t)1 << 5)  // PTE5

#define LOW 0	// FOR SETTING PIN LOW
#define HIGH 1	//FOR SETTING PIN HIGH
#define NUM_ROWS 2	//TOTAL NUMBER OF ROWS
#define NUM_COLS 4	//TOTAL NUMBER OF COLUMNS
#define COUNT 1024 //total number of buffer elements


/**************************************************
 * GLOBAL VARIABLES
 ***************************************************/
uint8_t row[2]={8,9}; //ROW,PORT PINS
uint8_t col[4]={2,3,4,5}; // COLUMN PORT PINS ARRAY



/**********************************************************************************************************************************
local function declartion
 ************************************************************************************************************************************/
void key_pressed(int r, int c);
void set_output(int r, int dir);
int read_input(int c);


/**********************************************************************************************************************************
 void delay() :
 @brief	simple loop to calculate delay
 @param 	interations: required delay in ms
 ************************************************************************************************************************************/

void delay(uint32_t iterations)
{
	iterations= iterations*5000;//Calibrating iterations

	while (iterations--!=0) {

		__asm volatile("NOP");
		__asm volatile("NOP");

	}
}


/**********************************************************************************************************************************
void play_freq(int freq , int key)
 @brief	    COMPUTE SINE FUNCTION AND PLAY THE TONE
 @param 	FREQ required frequency for sine function
 @return	void
 ************************************************************************************************************************************/
void play_freq(int freq )
{
	int sample;
	uint16_t buffs_op[COUNT];
	sample = tone_to_samples(freq, buffs_op, COUNT); //computes tone for specified frequency
	Copy_DMA_buffer(buffs_op, sample);//get buffer ready to be copied
	Start_DMA_transfer(); //starts transfer
	delay(500);
	TPM1->SC &= ~TPM_SC_CMOD_MASK; //stop note
}
/**************************************************
*  void init_keypad(void);
* @brief:    Initialize the 4x4 matrix keypad GPIO's
* @param:    none
* @return:	 none
 ***************************************************/
void init_keypad(void)
{
	// Keypad control pins:
	// PTB8: ROW0, PTB9: ROW1
	// PTE5: COL4, PTE4: COL3, PTE3: COL2, PTE2: COL1

	// Enable clock for PORTB, PORT 3
	SIM->SCGC5 |= (SIM_SCGC5_PORTB(1) |  SIM_SCGC5_PORTE(1));

	// Configure ROWS OF KEYPAD AS GPIO OUTPUT
	GPIOB->PDDR |= (ROW1 | ROW2); //PTB8,PTB9

	// Configure COLUMNS OF KEYPAS AS GPIO INPUT
	GPIOE->PDDR &= (~COL1 & ~COL2 & ~COL3 & ~COL4);  //PTE2,PTE3,PTE4,PTE5


	// column input pins //ENABLE PULL UPS
	PORTB->PCR[8] = (PORT_PCR_MUX(1) | PORT_PCR_PE(0)); // PTB8
	PORTB->PCR[9] = (PORT_PCR_MUX(1) | PORT_PCR_PE(0)); // PTB9


	PORTE->PCR[2] = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); // PTE2
	PORTE->PCR[3] = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); // PTE3
	PORTE->PCR[4] = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); // PTE4
	PORTE->PCR[5] = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); // PTE5
}

void keypad_scan(void)
{

	// assume all row outputs are high to start with
	for (int r=0; r < NUM_ROWS; r++) {
		//then set first row low
		set_output(r, LOW);
		//read column inputs
		for (int c=0; c<NUM_COLS; c++)
		{
			//if certain column pin reads low that key is pressed
			if (read_input(c) == LOW)
			{
				for(int i=0; i<100000 ;i++); //for software debounce

				if (read_input(c) == LOW)
				{
					key_pressed(r,c); //key is pressed for that row and column
				}


			}

		}
		set_output(r, HIGH); //set row high again
	}

}

/**************************************************
* void set_output(int r, int dir)
* @brief:   makes the port of required pin high or low
* @param:    r as pin number
* @return:	 dir as high or low
 ***************************************************/

void set_output(int r, int dir)
{
	if(dir == LOW)
	{
		GPIOB->PDOR &= (~ ((uint32_t)1 << row[r])); //sets port pin low
	}
	else if(dir == HIGH)
	{
		GPIOB->PDOR |=  ((uint32_t)1 << row[r]); //sets port pin high
	}
}
/**************************************************
* int read_input(int c)
* @brief:   reads the input of given pin
* @param:    c as pin number
* @return:	 input thats read
 ***************************************************/
int read_input(int c)
{

	return (GPIOE->PDIR &  ((uint32_t)1 << col[c]) ); //return value of pin read

}

/**************************************************
* void key_pressed(int r, int c)
* @brief:  figures out which key was pressed
* @param:    r as row pin
* @param	 c as column
* @return:	 input thats read
 ***************************************************/

void key_pressed(int r, int c)
{
	if(r==0)   //if row 0 check which column to find out which key was pressed
	{
		switch(c)
		{
		case 0:

			play_freq(SA); //play freq for first key
			break;
		case 1:
			play_freq(RE); //play freq for 2nd key
			break;
		case 2:
			play_freq(GA);//play freq for 3rd key
			break;
		case 3:
			play_freq(MA);//play freq for 4th key
			break;
		}

	}
	else if(r==1) //if row 1 check the column to determine which key was pressed
	{
		switch(c)
		{
		case 0:
			play_freq(PA); //play freq for 5th key
			break;
		case 1:
			play_freq(DHA);//play freq for 6th key
			break;
		case 2:
			play_freq(NI); //play freq for 7th key
			break;
		case 3:
			play_freq(SA);//play freq for 8th key
			break;
		}
	}
}


