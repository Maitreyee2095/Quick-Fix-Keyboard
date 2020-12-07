/*
 * keypad.h
 *
 *  Created on: Nov 26, 2020
 *      Author: MAITREYEE RAO
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define SA 261.63	//FREQUENCY FOR 'SA'-->C4
#define RE 293.67	//FREQUENCY FOR 'RE'-->D4
#define GA 329.63	//FREQUENCY FOR 'GA'-->E4
#define MA 349.63	//FREQUENCY FOR 'MA'-->F4
#define PA 392		//FREQUENCY FOR 'PA'-->G4
#define DHA 440		//FREQUENCY FOR 'DHA-->A4
#define NI 493.88	//FREQUENCY FOR 'NI'-->B4
#define SA_ 523.25	//FREQUENCY FOR HIGHER OCTAVE SA_ //C5 IN WESTERN NOTE

#define COUNT 1024

/**************************************************
Constants
***************************************************/
typedef enum
{
	KEY_sa,	//key1---ROW 0 COLUMN 1
	KEY_re,	//key2---ROW 0 COLUMN 2
	KEY_ga,	//key3---ROW 0 COLUMN 3
	KEY_ma,	//key4---ROW 0 COLUMN 4
	KEY_pa,	//key5---ROW 1 COLUMN 1
	KEY_dha,//key6---ROW 1 COLUMN 2
	KEY_ni,	//key7---ROW 1 COLUMN 3
	KEY_SA,	//key8---ROW 1 COLUMN 4
	NO_OF_KEYS,//total keys
}key_enm;

/**************************************************
Global Function Prototypes
***************************************************/

/**************************************************
*  void keypad_scan(void);
* @brief:    Scan keypad to check if key was pressed
* @param:    none
* @return:	 none
***************************************************/
 void keypad_scan(void);

/**************************************************
*  void init_keypad(void);
* @brief:    Initialize the 4x4 matrix keypad GPIO's
* @param:    none
* @return:	 none
***************************************************/
 void init_keypad(void);

 /**********************************************************************************************************************************
 void play_buffer()
  @brief	    plays out recorded tune.
  @param 	void
  @return	void
  ************************************************************************************************************************************/
 void play_buffer();

 /**********************************************************************************************************************************
  void delay() :
  @brief	simple loop to calculate delay
  @param 	interations: required delay in ms
  ************************************************************************************************************************************/

 void delay(uint32_t iterations);

#endif /* KEYPAD_H_ */
