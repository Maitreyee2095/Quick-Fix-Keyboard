/*
 * test_sin.c
 *this files test sine wave
 *  Created on: Nov 17, 2020
 *      Author: maitreyee rao
 */

#include "stdio.h"
#include "sin_trig.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <math.h>


/**********************************************************************************************************************************
 *void test_sine():test sine function
 *@param takes no parameters
 *@return void
 *This code is as given by Howdy pierce in the Assignment 7 writeup
 ************************************************************************************************************************************/

void test_sine()
{
double created_sin;
double actual_sin;
double error;
double sum_square = 0;
double max_error = 0;
int i= 0;
for (i=-TWO_PI; i <= TWO_PI; i++) {
actual_sin = sin( (double)i / TRIG_SCALE_FACTOR) * TRIG_SCALE_FACTOR;
created_sin = sin1(i);
error = created_sin - actual_sin;
if (error < 0)
error = -error;
if (error > max_error)
max_error = error;
sum_square += error*error;
}
printf("\n\r");
printf("\n\rmax_error=%f sum_square=%f\n\r", max_error, sum_square);
printf("\n\r");
}


