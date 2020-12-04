/*
 * piyu_bole.c
 *
 *  Created on: Dec 1, 2020
 *      Author: maitreyee rao
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
/********************************DEFINES********************************************************************/

#define DELAY1_MS 300 //delay
#define _NI 246.94 //lower ffrequency note b3

/********************************GLOBAL VARIABLES********************************************************************/
//notes for song
int piyu_note1[4]={SA,_NI,SA,RE};
int piyu_note2[4]={RE,GA,MA,GA};
int piyu_note3[3]={SA,PA,MA};
int piyu_note4[3]={RE,PA,MA};
int piyu_note5[4]={RE,GA,MA};




/**********************************************************************************************************************************
void play_note_piyu(int freq)
 @param freq input frequency to play note at that frequency
 @returns none
 ************************************************************************************************************************************/


void play_note_piyu(int freq)
{
	int sample3;

	uint16_t buffs_output2[COUNT];
	sample3 = tone_to_samples(freq, buffs_output2, COUNT); //computes tone for specified frequency
	Copy_DMA_buffer(buffs_output2, sample3);//get buffer ready to be copied
	Start_DMA_transfer();//Start transfer
	delay(DELAY1_MS);

}
/**********************************************************************************************************************************
 void piyu_bole(): Plays piyu_bole song.
 @param none
 @returns none
 ************************************************************************************************************************************/

void piyu_bole()
{
	int j =2;
	while(j--) //play first note twice
	{
		for(int i=0;i<4;i++)
		{
			play_note_piyu(piyu_note1[i]);
		}
		delay(DELAY1_MS);
		for(int i=0;i<4;i++)
		{
			play_note_piyu(piyu_note2[i]);
		}
		delay(DELAY1_MS);
		for(int i=0;i<4;i++)
		{
			play_note_piyu(piyu_note1[i]);
		}
		delay(DELAY1_MS);
		for(int i=0;i<3;i++)
		{
			play_note_piyu(piyu_note1[i]);
		}
		delay(DELAY1_MS);

		delay(DELAY1_MS);
		TPM1->SC &= ~TPM_SC_CMOD_MASK;//close the note
	}

	int m =2;
	while(m--) //play second note twice
	{

		for(int i=0;i<3;i++)
		{
			play_note_piyu(piyu_note3[i]);
		}
		for(int i=0;i<3;i++)
		{
			play_note_piyu(piyu_note4[i]);
		}
		//delay(100);
		for(int i=0;i<3;i++)
		{
			play_note_piyu(piyu_note3[i]);
		}
		for(int i=0;i<3;i++)
		{
			play_note_piyu(piyu_note4[i]);
		}
		//delay(100);
		for(int i=0;i<3;i++)
		{
			play_note_piyu(piyu_note3[i]);
		}


		for(int i=0;i<4;i++)
		{
			play_note_piyu(piyu_note2[i]);
		}
		delay(DELAY1_MS);
		delay(DELAY1_MS);


	}

	int k =2;
	while(k--) //play 3rd note twice
	{
		for(int i=0;i<4;i++)
		{
			play_note_piyu(piyu_note1[i]);
		}
		delay(DELAY1_MS);
		for(int i=0;i<4;i++)
		{
			play_note_piyu(piyu_note2[i]);
		}
		delay(DELAY1_MS);
		for(int i=0;i<4;i++)
		{
			play_note_piyu(piyu_note1[i]);
		}
		delay(DELAY1_MS);
		for(int i=0;i<3;i++)
		{
			play_note_piyu(piyu_note1[i]);
		}
		delay(DELAY1_MS);

		delay(DELAY1_MS);
		TPM1->SC &= ~TPM_SC_CMOD_MASK; //end note
	}


}

