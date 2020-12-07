/*
 * Command_process.c
 *
 *  Created on: Nov 9, 2020
 *      Author: maitreyee Rao
 *   some code from this file was used from the lexical analysis code that Howdy gave in lecture 11
 */

#include "Command_logger.h"
#include "Command_process.h"
#include "keypad.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "rabta.h"
#include "jinglebells.h"
#include "piyu_bole.h"
#define ENTER 0x0D
typedef void (*start_command)(const char* cmd); // Operating Using Function Pointers

typedef struct {
	const char* name;
	start_command handler;
} command_lookup_t;	//COMMAND LOOKUP TABLE

extern int record_song;
/*********************************************************************************************************
 * static void jingles(const char* cmd)): IF COMMAND IS JINGLES PLAYS THE JINGLE BELLS SONG
 **********************************************************************************************************/

static void jingles(const char* cmd)
{
	printf("\n\rPlaying jingle bells\n\r");
	jingle_bells();
}
/*********************************************************************************************************
 * static void song1(const char* cmd)): IF COMMAND IS Song1 plays song1 and prints info for the song
 **********************************************************************************************************/

static void song1(const char* cmd)
{
	printf("\n\rPlaying song:Raabta\n\r");
	printf("\n\rMovie:Agent Vinod\n\r");
	printf("\n\rSinger:Arjit Singh\n\r");
	printf("Music Director:Pritam\n\r");
	rabta();
}

/*********************************************************************************************************
 * static void song2(const char* cmd)): IF COMMAND IS Song2 plays song2 and prints info for the song
 **********************************************************************************************************/

static void song2(const char* cmd){
	printf("\n\rPlaying song:Piyu Bole\n\r");
	printf("\n\rMovie:Parineeta\n\r");
	printf("\n\rSinger:Sonu Nigam and Shreya Ghoshal\n\r");
	printf("Music :Shantanu Moitra\n\r");

	piyu_bole();

}
/*********************************************************************************************************
 * static void help(const char* cmd)): IF COMMAND IS help peints help menu for us
 **********************************************************************************************************/
static void record(const char* cmd)
{
	record_song=1;
}

/*********************************************************************************************************
 * static void help(const char* cmd)): IF COMMAND IS help peints help menu for us
 **********************************************************************************************************/
static void play(const char* cmd)
{
	play_buffer();

}
/*********************************************************************************************************
 * static void help(const char* cmd)): IF COMMAND IS help peints help menu for us
 **********************************************************************************************************/

static void help(const char* cmd){

	printf("\n\rEnter one of the following functions:\r\n");
	printf("'Song1'	:Play bollywood Rabta  song\r\n");
	printf("'Song2' :Play bollywood Piyu bole  song\r\n");
	printf("'jingle':Plays the jingle bells tune\r\n");
	printf("'record':Records the tunes played on keyboard\r\n");
	printf("'play'  :Plays back recorded tune\r\n");
	printf("'Help'  :Get the help menu\r\n");

}

/*********************************************************************************************************
 * static void unknown_command(const char* cmd): if unknown commands throws error msg
 **********************************************************************************************************/

static void unknown_command(const char* cmd){
	printf("Please Enter a valid command\n\r"); //if it doesnt match to any command throw an error
}
static const command_lookup_t commands[] = {
		{"song1", song1},
		{"jingle", jingles},
		{"help", help},
		{"song2",song2},
		{"record",record},
		{"play", play},
		{"", unknown_command}
};
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
 *   This  code was from Prof Howdy's lecture series
 **********************************************************************************************************/
void process_command(char *input) //code from Prof Howdy's lecture 11
{

	char *p = input;
	char *end;
	char *argv[10];
	int argc = 0;
	// find end of string
	for (end = input; *end != '\0'; end++)
		;

	// Tokenize input in place
	bool in_token = false;
	memset(argv, 0, sizeof(argv));
	for (p = input; p < end; p++) {

		if(in_token && isspace(*p))  // if token is true
		{
			*p='\0'; //append the string
			in_token=false;//change token to false


		}
		else if(!in_token &&!(isspace(*p)) )//if anything other than space//if token is false
		{

			argv[argc++]= p; //add character to argv array
			argc++;//increment argc
			in_token=true; //change token
			if(argc == sizeof(argv)/sizeof(char*) - 1)
				break;


		}


	}
	argv[argc] = NULL;//append string
	if (argc == 0)   // no command
		return;

	int num_commands = sizeof(commands) / sizeof(command_lookup_t);
	// TODO: Dispatch argc/argv to handler
	for(int i=0; i<num_commands;i++)
	{
		if(strncasecmp(argv[0], commands[i].name,strlen(commands[i].name)) == 0) //compare argument with command
		{
			commands[i].handler(*argv); //dispatch to command handler
			break;
		}

	}


}



