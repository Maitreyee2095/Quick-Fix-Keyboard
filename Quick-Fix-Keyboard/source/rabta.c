/*
 * rabta.c
 *
 *  Created on: Nov 30, 2020
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

#define DELAY_MS 300 //DELAY
#define RE_ 587.33 //HIGHER NOTE D6
#define GA_ 659.26//HIGHER NOTE E6
#define MA_ 698.46 //HIGHER NOTE F6
#define PA_ 783.99//HIGHER NOTE A6
/********************************GLOBALS********************************************************************/
//NOTES FOR SONG
int note1[32]={PA,NI,SA_,NI,SA_,NI,RE_,SA_,PA,NI,SA_,NI,SA_,NI,RE_,SA_,PA,NI,SA_,NI,SA_,NI,RE_,SA_,PA,NI,SA_,NI,SA_,NI,RE_,SA_};
int note2[8]={DHA,SA_,RE_,SA_,RE_,SA_,GA_,RE_};
int note3[24]={RE_,SA_,SA_,NI,NI,DHA,DHA,PA,PA,DHA,NI,DHA,NI,SA_,RE_,GA_,GA_,RE_,GA_,RE_,GA_,RE_,GA_,PA_};
int note4[8]={GA_,RE_,GA_,RE_,GA_,RE_,GA_,PA_};
int note5[12]={MA_,GA_,RE_,SA_,NI,SA_,NI,SA_,NI,SA_,NI,SA_};
int note6[5]={GA_,GA_,DHA,PA,DHA};
int note7[6]={PA,MA_,GA_,RE_,RE_,GA_};
int note8[24]={RE_,SA_,SA_,NI,NI,DHA,DHA,PA,PA,DHA,NI,DHA,NI,SA_,RE_,GA_,PA,NI,SA_,NI,SA_,NI,RE_,SA_};




/**********************************************************************************************************************************
void play_note_piyu(int freq)
 @param freq input frequency to play note at that frequency
 @returns none
 ************************************************************************************************************************************/


void play_note_rabta(int freq)
{
	int sample2;
	uint16_t buffs_output1[COUNT];
	sample2 = tone_to_samples(freq, buffs_output1, COUNT); //computes tone for specified frequency
	Copy_DMA_buffer(buffs_output1, sample2);//get buffer ready to be copied
	Start_DMA_transfer();
	delay(DELAY_MS);

}
/****************************************************************************************************

void RABTA(): Plays NOTES FOR RABTA song.
 @param none
 @returns none


****************************************************************************************************/


void rabta()
{

	for(int i=0;i<33;i++)
	{
		play_note_rabta(note1[i]);

	}

	int jK=2;
	while(jK--)
	{
		for(int i=0;i<7;i++)
		{
			play_note_rabta(note2[i]);

		}


	}


	for(int i=0;i<24;i++)
	{

		play_note_rabta(note3[i]);

	}
	play_note_rabta(note4[8]);

	for(int i=0;i<13;i++)
	{
		play_note_rabta(note5[i]);

	}


	for(int i=0;i<6;i++)
	{
		play_note_rabta(note6[i]);

	}


	int K=1;
	while(K--)
	{

		for(int i=0;i<9;i++)
		{
			play_note_rabta(note4[i]);

		}

		for(int i=0;i<13;i++)
		{
			play_note_rabta(note5[i]);

		}

		for(int i=0;i<6;i++)
		{
			play_note_rabta(note6[i]);

		}


	}

	int l=2;
	while(l--)
	{
		for(int i=0;i<5;i++)
		{
			play_note_rabta(note7[i]);

		}

	}
	delay(300);
	for(int i=0;i<25;i++)
	{
		play_note_rabta(note8[i]);

	}


}
