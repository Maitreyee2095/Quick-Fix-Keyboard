/*
 * Circular_buffer.h
 *
 *  Created on: Nov 1, 2020
 *      Author: maitr
 *
 *      Parts of the code was inspired from Alexander .G Dean
 *      https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 *      The .h file is used from Howdy's implementation of cbfifo.h
 */

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_
#include <stdint.h>
#include <MKL25Z4.h>
#include <stdlib.h>  // for size_t
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/*****************************************DEFINES*****************************************************************/
#define BUFF_MAX 256	//MAX Circular Buffer Size
#define STARTCRITICAL()	__disable_irq() //inspired from deans code
#define ENDCRITICAL(x)	__set_PRIMASK(x)//inspired from deans code
#define min(x,y) ((x)<(y)?(x):(y))
/********************************************************************************************************************/
typedef struct {
	int write;
	int read;
	size_t capacity;
	bool Full;
	uint8_t data[BUFF_MAX];
} cb_t;
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
void cb_init(cb_t * c);
/***************************************************************************************************************************
 * Checks if Circular Buffer is empty
 *
 * Parameters:
 *  c			pointer to struct cb_t
 *
 * Returns:
 *   True if empty
 *   False if not
 ********************************************************************************************************************************/
bool cb_Empty(cb_t * c);
/***************************************************************************************************************************
 * Total Circular Buffer Size
 *
 *
 * Parameters:
 * c		 pointer to struct cb_t
 *
 * Returns:
 *   Size as integer value
 ********************************************************************************************************************************/
int cb_Size(cb_t * c);
/***************************************************************************************************************************
 * Checks if Circular Buffer is Full
 *
 * Parameters:
 *  c			pointer to struct cb_t
 *
 * Returns:
 *   True if Full
 *   False if not
 ********************************************************************************************************************************/
bool cb_Full(cb_t * c);
/*******************************************************************************************************************************
 * Returns the number of bytes currently on the Circular Buffer.
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   Number of bytes currently available to be dequeued from the Circular Buffer.
 *********************************************************************************************************************************/
size_t cb_Length(cb_t * c);
/*********************************************************************************************************************************
 * Enqueues data onto the Circular Buffer, up to the limit of the available Circular Buffer
 * capacity.
 *
 * Parameters:
 * 	 c			pointer to typedef structure cb_t
 *   buffer     Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 *
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns -1.
 ***********************************************************************************************************************************/
size_t cb_Enqueue(cb_t * c, const void *buffer , size_t nbyte);


/**********************************************************************************************************************************
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * Circular Buffer. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 * 	 c		  pointer to typedef structure cb_t
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 *
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte.
 *
 ********************************************************************************************************************************/
size_t cb_Dequeue(cb_t * c,void *buf, size_t nbyte);






#endif /* CIRCULAR_BUFFER_H_ */
