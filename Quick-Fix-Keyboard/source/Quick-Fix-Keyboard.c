/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Quick-Fix-Keyboard.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */
#include "keypad.h"
#include "DAC_config.h"
#include "analog_out.h"
#include "Uart.h"
#include "Command_logger.h"
#include "rabta.h"
#include "piyu_bole.h"
#include "test_sin.h"
#include "test_cbfifo.h"
/* TODO: insert other definitions and declarations here. */

/**********************************************MAIN*********************************************************************/


int main(void) {

	/* Init board hardware. */

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif


	// TODO:e
	UART_init(38400);//set baud rate to 38400
	printf( "\n\rWelcome to QUICK-FIX KEYBOARD \n\r");
	Init_DAC();			//Initialize DAC
	Init_TPM1();		//Initialize TPM1 for DAC
	Init_DMA();			//Initialize DMA
	init_keypad();		//Initialize Keypad
	printf( "\n\rTesting Sine Function.....\n\r");
	test_sine();		//test sine function
	test_cbfifo();		//test circular buffer


	printf("\n\rEnter one of the following functions:\r\n");
	printf("'Song1' :Play bollywood Rabta  song\r\n");
	printf("'Song2' :Play bollywood Piyu bole  song\r\n");
	printf("'jingle' : Plays the jingle bells tune\r\n");
	printf("'Help' : Get the help menu\r\n");
	while(1) {
		printf("\r\n ? ");
		command_input();//check if there's any input on UART


	}
	return 0 ;
}
