/*
 * Command_logger.h
 *
 *  Created on: Nov 1, 2020
 *      Author: maitreyee
 */

#ifndef COMMAND_LOGGER_H_
#define COMMAND_LOGGER_H_

#include "Circular_buffer.h"
#include "UART.h"

#include "MKL25Z4.h"
#include "core_cm0plus.h"
/**********************************************************************************************************
 * void command_input()
 * Accepts commands from the user
 *
 *************************************************************************************************************/
void command_input();


extern cb_t TxQ, RxQ;


#endif /* COMMAND_LOGGER_H_ */
