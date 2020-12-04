/*
 * sin_trig.c
 * this file computes a sine wave
 *
 *  Created on: Nov 16, 2020
 *      Author: maitreyee rao
 *    Some parts of the code were inspired from Howdy Pierce lecture series lecture 24
 *
 */



#include "sin_trig.h"
#include "MKL25Z4.h"
#include "stdio.h"
#include "stdint.h"
#include "assert.h"

#define TRIG_TABLE_STEPS 	(32)
#define TRIG_TABLE_STEP_SIZE (HALF_PI/TRIG_TABLE_STEPS)
/****************************************************************************************************
*lookup table: looke up table with values for sin from 0-PI/2
*for PI/2- PI - we know that   sin(x)=sin(PI-x)
*for 0-PI- we know that        sin(-x)= -(sin)x
*as all values can be calculated from values for 0-PI/2 we use only these values in lookup table
*to use only integer maths we scale all the values using scale factor
*this table was referenced from Prof. Howdy Pierece's lecture
****************************************************************************************************/

static const int16_t sin_lookup[TRIG_TABLE_STEPS+1] =
  {0, 100, 200, 299, 397, 495, 591, 686, 780, 871, 960, 1047,
   1132, 1214, 1292, 1368, 1440, 1509, 1575, 1636, 1694, 1747,
   1797, 1842, 1882, 1918, 1949, 1976, 1998, 2015, 2027, 2035,
   2037};
/**********************************************************************************
*int32_t sin1(int32_t x):function to generate sine wave
*@parameter :int32_t x: takes parameter integer x ,value of angle
*@returns returns integer value which is nothing but sin(x)
*the function was built on basis of Howdy Pierce, lecture series lecture no 24
**********************************************************************************/

int32_t sin1(int32_t x)
{
  int32_t index;//to keep track of index
  int temp = 1; // to keep track of sign

  //check value of x, if x<-PI get x in the required bounds -PI<x<PI by adding TWO_PI repeatedly
  while (x < -PI)
     x += TWO_PI;

  //check value of x, if x>PI get x in the required bounds -PI<x<PI by subtracting TWO_PI
   while (x > PI)
     x -= TWO_PI;
  //make sure x is within bounds -PI<x<PI
  assert(-PI <= x && x <= PI);

  // if x<0 we know that sin(-x)=-sinx; so change x to +x and change temp to -ve
  if (x < 0) {
    x = -x;
    temp = -1;//this is just to keep track of sign
  }

  //  if x>pi/2 we know that sin(x)=sin(pi-x); so change x to pi-x
  if (x > HALF_PI)
    x = PI - x;

  //White, in her chapter 9 of Making Embedded systems suggests
  //To use the table, you’ll need to calculate the index that matches your input.
  //to do this we need to subtract lowest value from x and divide by step size, for us the lowest value is 0
  index =  x / TRIG_TABLE_STEP_SIZE;
  int32_t x1 = index * TRIG_TABLE_STEP_SIZE;

  	//if x1 == x its present in lookup table
   if (x1 == x)
    return temp * sin_lookup[index];//temp is sign so multiply it to the value from lookup table to get values for 0 to -PI

  // else, interpolate and find the middle point
  int32_t x2 = (index+1) * TRIG_TABLE_STEP_SIZE;
  int32_t interpolate_x2 = interpolate(x, x1, sin_lookup[index], x2, sin_lookup[index+1]);

  return temp * interpolate_x2;
}

/**********************************************************************************************************************************
*int32_t interpolate(int32_t x0, int32_t x1, int32_t y1, int32_t x2, int32_t y2): function to find the middle value , between two points present in lookup table
*@parameter :int32_t x0: takes parameter x0, x co-ordinate of the point in middle of two points
*@parameter :int32_t x1,int32_t y1:(x1,y1) one of the previous points on the curve
*@parameter :int32_t x1,int32_t y1:(x2,y2) one of the other points on the curve
          |       .
          |       (x2,y2)
          |   .(x0,y0)
          | .
          |(x1,y1)
__________|_____________________
          |

*@returns returns integer value y0, which is y co-ordinate
************************************************************************************************************************************/


int32_t interpolate(int32_t x0, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
  return ( (((x2 - x1)/2) + ((x0 - x1) * (y2 - y1))) / (x2 - x1) + y1);
}
