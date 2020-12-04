/*
 * Command_Logger.C
 *
 *  Created on: Nov 1, 2020
 *   Author: maitreyee Rao
 *
 *
 *
 */


#include "Command_logger.h"
#include "Command_process.h"
#include "keypad.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define ENTER 0X0D
#define BACKSPACE 0X08
#define MAX_BUFFER 1024

/**********************************************************************************************************
 * void command_input()
 * Accepts commands from the user
 *
 *************************************************************************************************************/

void command_input()
{
	char buffer[MAX_BUFFER];
	uint8_t cha;
	size_t size;
	int i=0;

	while (1)
	{


		while (cb_Length(&RxQ) == 0)//wait till something arrives on rx buffer
		{
			keypad_scan();
		}



		size =cb_Dequeue(&RxQ,&cha,1);//dequeue one character
		assert(size==1);
		putchar(cha);

		if(cha == ENTER) //check if user pressed enter
		{
			buffer[i]='\0'; //append the string if user pressed enter
			break;

		}
		else if(cha == BACKSPACE ) //check if user pressed backspace
		{
			printf(" \b"); // make the backspace act like the backspace clear the character entered previously
			i--; // to clear it from buffer just over write it
		}
		else
		{
			buffer[i]=cha; // add character to the buffer
			i++;

		}

	}

	printf("\n\r");

	process_command(buffer); // send string to process

}


//


