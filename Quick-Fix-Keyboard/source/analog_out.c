/*
 * analog_out.c
This file contains
tone_to_buffer, which fills buffer with tone,
initialization of TPM1
DMA initialization andm transfer function
 *  Created on: Nov 17, 2020
 *      Author: maitreyee Rao
 *      credit : Parts of code was inspired from Alexander G Dean
 */





#include "assert.h"

#include "stdint.h"

#include "stdio.h"
#include "sin_trig.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "math.h"
#include "analog_out.h"


#define PLAYOUT_FREQ 48000 //frequency 48Khz
#define BUFF_MAX 1024


uint16_t temp[BUFF_MAX];
uint16_t Reload_DMA_Source[BUFF_MAX]; //buffer to load dma
uint32_t Reload_DMA_Byte_Count=0; //buffer for dma count
uint32_t DMA_Playback_Count=0;
/**********************************************************************************************************************************
 *size_t tone_to_samples(int freq, uint16_t *buff, size_t size):  computes the samples representing a pure tone of a
specified frequency, based on your sin(x) function
 *@parameter :int freq: freq parameter is input frequency
 *@parameter :uint16_t *buff:buffer to be filled
 *@parameter :size_t size:total size of buffer

 *@returns returns size_t total samples
 ************************************************************************************************************************************/

size_t tone_to_samples(int freq, uint16_t *buff, size_t size) {

	int32_t temp1;
	int i=0;
	int number_of_times = size / ((PLAYOUT_FREQ + (freq/2)) / freq);//total number of cycles required
	int samples = ((PLAYOUT_FREQ + (freq/2)) / freq) * number_of_times;//total samples required
	int16_t period_in_samples=((PLAYOUT_FREQ + (freq/2)) / freq); //playout period
	for (i=0; i < samples; i++) {

		temp1 = sin1(i * TWO_PI /period_in_samples  ) + (100*TRIG_SCALE_FACTOR);
		buff[i]=temp1;

	}




	return samples;
}
/**********************************************************************************************************************************
 *void Init_TPM1():Function to Initialize TPM1
 *takes no arguments
 *returns void
 *this function was built with reference to code by ALexander G Dean
 *https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
 ************************************************************************************************************************************/

void Init_TPM1()
{

	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	//set clock source for tpm
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	// disable TPM
	TPM1->SC = 0;
	// Load the mod and counter
	TPM1->MOD = TPM_MOD_MOD(CLOCK / (CLOCK/1000));
	TPM1->CNT = 0;
	//prescaler set to 0//include dma//include cmod
	TPM1->SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0) | TPM_SC_CMOD(1) | TPM_SC_DMA_MASK;
}
/**********************************************************************************************************************************
 *void Init_DMA():Function to Initialize DMA
 *takes no arguments
 *returns void
 *this function was built with reference to code by ALexander G Dean
 *https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
 ************************************************************************************************************************************/

void Init_DMA() {


	// Gate clocks to DMA and DMAMUX
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	// Disable DMA channel to allow configuration
	DMAMUX0->CHCFG[0] = 0;

	// Generate DMA interrupt when done
	// Increment source, transfer words (16 bits)
	// Enable peripheral request
	DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK|
			DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) |
			DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;

	// Configure NVIC for DMA ISR
	NVIC_SetPriority(DMA0_IRQn, 1);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	// Enable DMA MUX channel with TPM1 overflow as trigger
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(55);

}
/**********************************************************************************************************************************
 *void Copy_DMA_buffer(uint16_t *source, uint32_t count):copy source buffer contents to buffer that is passed to DMA
 *@param uint16_t *source: pointer to source buffer
 *@param uint32_t count: total values in buffer
 *this function was built with reference to code by ALexander G Dean
 *https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
 ************************************************************************************************************************************/

void Copy_DMA_buffer(uint16_t *source, uint32_t count)
{
	//stop tpm1
	TPM1->SC &= ~TPM_SC_CMOD_MASK;
	memcpy(Reload_DMA_Source, source, count*2);
	//Reload_DMA_Source = source;
	Reload_DMA_Byte_Count = count;
	//start tpm1
	TPM1->SC |= TPM_SC_CMOD(1);
}
/**********************************************************************************************************************************
 *void Start_DMA_transfer():start DMA transfer copy contents from buffer to DAC
 *takes no arguments
 *returns void
 *this function was built with reference to code by ALexander G Dean
 *https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
 ************************************************************************************************************************************/

void Start_DMA_transfer() {


	// initialize source and destination pointers
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) Reload_DMA_Source);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t)&(DAC0->DAT[0]));
	// byte count
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(Reload_DMA_Byte_Count*2);
	// clear done flag
	DMA0->DMA[0].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;
	// set enable flag
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;

}

void DMA0_IRQHandler(void) {

	// start done flag
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
	//start dma transfer
	Start_DMA_transfer();


}
