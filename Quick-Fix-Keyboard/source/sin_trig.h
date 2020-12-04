/*
 * sin_trig.h
 *
 *  Created on: Nov 16, 2020
 *      Author: maitreyee RAO
 */

#ifndef SIN_TRIG_H_
#define SIN_TRIG_H_
#include <stdint.h>
#include "math.h"

/********************************************DEFINES*****************************************/
//these were referenced from Howdy Pierece's lecture
#define TRIG_SCALE_FACTOR	(2037)//to use only integer maths we scale all the values using scale factor
#define HALF_PI				(3200)
#define PI 					(6399)
#define TWO_PI				(12799)

/**********************************************************************************
*int32_t sin1(int32_t x):function to generate sine wave
*@parameter :int32_t x: takes parameter integer x ,value of angle
*@returns returns integer value which is nothing but sin(x)
**********************************************************************************/
int32_t sin1(int32_t x);
/**********************************************************************************************************************************
*int32_t interpolate(int32_t x0, int32_t x1, int32_t y1, int32_t x2, int32_t y2): function to find the middle value , between two points present in lookup table
*@parameter :int32_t x0: takes parameter x0, x co-ordinate of the point in middle of two points
*@parameter :int32_t x1,int32_t y1:(x1,y1) one of the previous points on the curve
*@parameter :int32_t x1,int32_t y1:(x2,y2) one of the other points on the curve
          |     .
          |     (x2,y2)
          |  .(x0,y0)
          | .
          |(x1,y1)
          |_____________________
          |
*@returns returns integer value y0, which is y co-ordinate
************************************************************************************************************************************/

int32_t interpolate(int32_t x0, int32_t x1, int32_t y1, int32_t x2, int32_t y2);






#endif /* SIN_TRIG_H_ */
