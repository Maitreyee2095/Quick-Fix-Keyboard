/*
 * DAC_config.c
 * This function contains DAC initialization
 *  Created on: Nov 17, 2020
 *      Author: maitreyee Rao
 *      credit : Parts of code was inspired from Alexander G Dean
 */


#include "sin_trig.h"
#include "MKL25Z4.h"
#include "stdio.h"
#include "stdint.h"
#include "DAC_config.h"
/**********************************************************************************************************************************
 *void Init_DAC():Function to Initialize DAC
 *takes no arguments
 *returns void
 *this function was built with reference to code by ALexander G Dean
 *https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
 ************************************************************************************************************************************/

void Init_DAC(void) {
  // Init DAC output

	SIM->SCGC6 |= (1UL << SIM_SCGC6_DAC0_SHIFT);
	SIM->SCGC5 |= (1UL << SIM_SCGC5_PORTE_SHIFT);

	PORTE->PCR[DAC_POS] &= ~(PORT_PCR_MUX(7));	// Select analog port pin

	// Disable buffer mode
	DAC0->C1 = 0;
	DAC0->C2 = 0;

	// Enable DAC, select VDDA as reference voltage
	DAC0->C0 = (1 << DAC_C0_DACEN_SHIFT) |
							(1 << DAC_C0_DACRFS_SHIFT);

}

