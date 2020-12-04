/*
 * Command_process.h
 *
 *  Created on: Nov 9, 2020
 *      Author: maitreyee rao
 */

#ifndef COMMAND_PROCESS_H_
#define COMMAND_PROCESS_H_

#include "Circular_buffer.h"
#include "UART.h"

#include "MKL25Z4.h"
#include "core_cm0plus.h"

/*********************************************************************************************************
 * void process_command(char*input): performs a lexical analysis on string thats entered
 * splits the string using ' ' (space) as token
 * when a ' ' is detected it appends the string and stores it in array argv[]
 * argc returns the number of elements of the array argv[]
 *
 * depending on argc it passed the output argv[] to different command handlers
 *
 * @param
 * input    String to be parsed
 *
 * @returns null
 **********************************************************************************************************/
void process_command(char *input); //code from Prof Howdy's lecture

/*********************************************************************************************************
void command2(char* cmd,char* address, char* length)
processes commands with argc 3 i.e 3 strings it checks if the first string matches command and passes further for function

@param
cmd        command
address    second string address for hex dump
length      third string length for hexdump

@returns void

 **********************************************************************************************************/

void command2(char* cmd);
/*********************************************************************************************************
void command2(char* cmd,char* address, char* length)
processes commands with argc 1 i.e 1 strings it checks if the first string matches command and processes further
@param
cmd        command
p

@returns void

**************************************************************************************************************/
void command1(char *cmd);

#endif /* COMMAND_PROCESS_H_ */
