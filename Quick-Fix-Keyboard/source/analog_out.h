/*
 * analog_out.h
 *
 *  Created on: Nov 17, 2020
 *      Author: maitreyee Rao
 *      credit : Parts of code was inspired from Alexander G Dean
 *
 */

#ifndef ANALOG_OUT_H_
#define ANALOG_OUT_H_

#include "stdint.h"
#define CLOCK		(48e6) //sys clock
/**********************************************************************************************************************************
*size_t tone_to_samples(int freq, uint16_t *buff, size_t size):  computes the samples representing a pure tone of a
specified frequency, based on your sin(x) function
*@parameter :int freq: freq parameter is input frequency
*@parameter :uint16_t *buff:buffer to be filled
*@parameter :size_t size:total size of buffer

*@returns returns size_t total samples
************************************************************************************************************************************/

size_t tone_to_samples(int freq, uint16_t *buff, size_t size);
/**********************************************************************************************************************************
*void Init_DMA():Function to Initialize DMA
*takes no arguments
*returns void
*this function was built with reference to code by ALexander G Dean
*https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
************************************************************************************************************************************/

void Init_DMA();
/**********************************************************************************************************************************
*void Init_TPM1():Function to Initialize TPM1
*takes no arguments
*returns void
*this function was built with reference to code by ALexander G Dean
*https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
************************************************************************************************************************************/

void Init_TPM1();
/**********************************************************************************************************************************
*void Copy_DMA_buffer(uint16_t *source, uint32_t count):copy source buffer contents to buffer that is passed to DMA
*@param uint16_t *source: pointer to source buffer
*@param uint32_t count: total values in buffer
*this function was built with reference to code by ALexander G Dean
*https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
************************************************************************************************************************************/

void Copy_DMA_buffer(uint16_t *source, uint32_t count);
/**********************************************************************************************************************************
*void Start_DMA_transfer():start DMA transfer copy contents from buffer to DAC
*takes no arguments
*returns void
*this function was built with reference to code by ALexander G Dean
*https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/DMA.c
************************************************************************************************************************************/

void Start_DMA_transfer();
#endif /* ANALOG_OUT_H_ */
