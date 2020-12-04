/*
 * jinglebells.c
 *
 *  Created on: Nov 30, 2020
 *      Author: maitreyee Rao
 *
 *      In this file there is function to play notes for jingle bells
 *      every line notes are stored in and array
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
/********************************GLOBAL VARIABLES********************************************************************/
//NOTE 1 : is line 1 ,2and line 4,5 of jingle bells as the lines have same notes are stored in a single array
int jb_note1[20]={GA,GA,GA,GA,GA,GA,GA,PA,SA,RE,GA,MA,MA,MA,MA,MA,GA,GA,GA,GA};
//delay for note1
int jb_n1_delay[20]={300,300,300,300,300,300,300,300,400,150,300,300,300,300,300,300,300,300,50,300};
int jb_n1_delay1[20]={0,0,300,0,0,300,0,0,0,0,300,0,0,0,0,0,0,0,0,0};
//jb_note2 : is line 3
int jb_note2[6]={GA,RE,RE,GA,RE,PA};
//delay for line 3
int jb_n2_delay[6]={300,300,300,300,300,300};
int jb_n2_delay1[6]={0,0,0,0,300,300};
// jb_note3 is line 6
int jb_note3[5]={PA,PA,MA,RE,SA};
int jb_n3_delay[5]={300,300,300,300,300};
int jb_n3_delay1[5]={0,0,0,0,300};


/**************************************************
 * @function: update_key_status
 * @brief:    This function updates pressed key status
 * @param:    key_event- The pressed key value
 * @return:	 none
 ***************************************************/
void play_note(int freq,int count,int count1)
{
	int sample1;
	uint16_t buffs_output[COUNT];

	sample1 = tone_to_samples(freq, buffs_output, COUNT); //computes tone for specified frequency
	Copy_DMA_buffer(buffs_output, sample1);//get buffer ready to be copied
	Start_DMA_transfer();//start copy
	delay(count); //delay
	TPM1->SC &= ~TPM_SC_CMOD_MASK; //stop TPM to stop playing tune
	delay(count1); //delay
}
void jingle_bells()
{
   //play note 1 :
	for(int i=0;i<20;i++)
	{
		play_note(jb_note1[i],jb_n1_delay[i],jb_n1_delay1[i]);
	}

	//play note2 :
	for(int i=0;i<6;i++)
	{
		play_note(jb_note2[i],jb_n2_delay[i],jb_n2_delay1[i]);
	}
//play note 3
	for(int i=0;i<20;i++)
	{
		play_note(jb_note1[i],jb_n1_delay[i],jb_n1_delay1[i]);
	}
//play NOTE 4
	for(int i=0;i<5;i++)
	{
		play_note(jb_note3[i],jb_n3_delay[i],jb_n3_delay1[i]);
	}

	delay(2000);


}
