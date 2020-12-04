/*
 * Circulat_buffer.c
 *
 *  Created on: Nov 1, 2020
 *      Author: Maitreyee Rao
 *       Parts of the code was inspired from Alexander .G Dean
 *      https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 */

#include "MKL25Z4.h"
#include "Circular_buffer.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
/***************************************************************************************************************************
 * Initializes Circular buffer
 * initializes the write read capacity and initializes data with an '_' as inital value
 *
 * Parameters:
 *  c		pointer to struct cb_t
 *
 * Returns:
 *   void
 ********************************************************************************************************************************/
//this code was inspired from dean's code
void cb_init(cb_t * c) {
	for (int i=0; i<BUFF_MAX; i++)
		c->data[i] = '_';	//fill the buffer with _ when initialized
	c->write = 0;			//initialize write to 0
	c->read = 0;			//initialize read to 0
	c->Full = false;
	c->capacity = BUFF_MAX;		//initialize buffer to BUFF_MAX size

}

bool cb_Empty(cb_t * c) {
	assert(c);
	return (c->write == c->read);  //empty condition //this code was inspired from dean's code
}

int cb_Size(cb_t * c) {
	assert(c);
	return( c->capacity); //return capacity //this code was inspired from dean's code
}

bool cb_Full(cb_t * c){
	assert(c);
	return (cb_Length(c) == BUFF_MAX);// full condition return length as BUFF_MAX//this code was inspired from dean's code
}

size_t cb_Length(cb_t * c){
	uint32_t masking;
	size_t value=0;

	masking = __get_PRIMASK();
	STARTCRITICAL(); //start critical disable interrupts during implementation of b=code given below

	if(c->Full){	//if circular buffer is full
		value = BUFF_MAX; //update length value to BUFF_MAX
	}
	else if(c->write >= c->read){
		value = c->write - c->read; //if write >= read update length value to write -read
	}
	else {
		value = BUFF_MAX - (c->read - c->write);//if read >= write update length value to BUFF_MAX-(read-write) condition after write wraps around

	}
	ENDCRITICAL(masking);
	return value;
}

/*********************************************************************************************************************************
 * Enqueues data onto the Circular Buffer, up to the limit of the available Circular Buffer
 * capacity.
 *
 * Parameters:
 * 	 c			pointer to typedef structure cb_t
 *   buffer     Pointer to the data
 *   nbyte    BUFF_MAX number of bytes to enqueue
 *
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns -1.
 ***********************************************************************************************************************************/

size_t cb_Enqueue(cb_t * c, const void *buffer , size_t nbyte) {
	size_t length1 = 0, length2=0;
	uint32_t masking;

	if(c->Full) {
		return 0;  //if buffer full return
	}

	masking = __get_PRIMASK();
	STARTCRITICAL(); //start critical section disable irqs

	if(cb_Empty(c)) {			    		//if buffer is empty
		c->write = length1 = nbyte;
		if(nbyte == BUFF_MAX) {
			//if input nbyte length is equal to BUFF_MAX length
			length1 = BUFF_MAX;
			c->Full = true; //update full
			c->write = 0;
		}
		memcpy(c->data, buffer, length1);//copy data to buffer
		c->read = 0;
		ENDCRITICAL(masking); //enable irqs
		return length1 + length2; //return length
	}

	if(c->read < c->write) //if read <write
	{
		length1 = min(nbyte, BUFF_MAX - c->write); //check how much bytes are left by BUFF_MAX-c->wrtie and compare number of bytes to enqueue and bytes to copy
		//choose whichever is minimum and copy it to buffer at from position write
		memcpy(c->data + c->write, buffer, length1);
		c->write += length1;//update write to new position


		if (c->write < BUFF_MAX) //check if buffer has still some space
		{
			ENDCRITICAL(masking);
			return length1 + length2;
		}

		c->write = 0; // Handle Full State
		if(c->read == 0) {
			c->Full = true;
			ENDCRITICAL(masking);
			return length1 + length2;
		}

		nbyte -= length1; //update nbytes and buffer
		buffer += length1;
	}


	length2 = min(nbyte, c->read - c->write);  //check which is remaining
	memcpy(c->data + c->write, buffer, length2);//copy contents to buffer at write pointer
	c->write += length2;

	if(c->write == c->read) //handle full state
	{
		c->Full = true;
	}

	ENDCRITICAL(masking);
	return length1 + length2;

}

size_t cb_Dequeue(cb_t * c, void *buffer , size_t nbyte) {

	size_t length1 = 0, length2=0;
	uint32_t masking;

	masking = __get_PRIMASK();

	STARTCRITICAL();//start critical section

	if(cb_Empty(c) && !c->Full) //check if buffer is empty return if empty
	{
		ENDCRITICAL(masking);
		return length1;
	}

	c->Full = false;//update full to false

	length1 = min(nbyte, BUFF_MAX - c->read); //check which is minimum no of bytes to read or bytes to read on buffer
	if((c->write > c->read) && (length1 > c->write - c->read)) //if write is greater than read and length is greater than bytes available to read
	{
		length1 = c->write - c->read; //update length to available bytes to read
	}
	memcpy(buffer, c->data + c->read, length1); //copy them to buffer , dequeue them
	c->read += length1; //update read
	if(c->read < BUFF_MAX) //check if read pointer has reached the last element
	{
		ENDCRITICAL(masking);
		return length1 + length2;
	}


	length2 = min(nbyte - length1, c->write); //check what is left now to read
	memcpy(buffer+length1, c->data, length2); //dequeue remaining
	c->read = length2;

	ENDCRITICAL(masking);
	return length1 + length2;

}




