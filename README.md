# Quick-Fix-Keyboard
## PES-Project
### TECH USED
* GPIO LINES
* DMA
* DAC
* UART
* COMMAND PROCESSING
* CIRCULAR BUFFERS

THIS PROJECT IS IMPLEMENTATION OF MOST OF THE THINGS LEARNT IN THE COURSE ECEN 5813:PRINCIPLES OF EMBEDDED SYSTEMS TAUGHT BY: HOWDY PIERCE

#### OBJECTIVE : 
To create a piano using FRDM KL25Z, keyboard matrix and speaker for output.The Piano would have 8 keys, arranged in a matrix form of 2X4 matrix representing 8 classical Indian notes namely 'Sa' , 'Re','Ga','Ma','Pa', 'Dha','Ni', 'Sa'.

#### [SUPPLEMENT PART] : 
TO add a functionality , where when user enters the name of the song it plays the saved tune.

#### BOARD DESIGN :
As the FRDM KL25Z board already has internal pull up resistors so haven't added any external pull ups.
Used a RC filter for speaker, to reduce noise.

![Image1](https://github.com/Maitreyee2095/Quick-Fix-Keyboard/blob/main/photos/Quick-fix-keyboard-schematic.png)
Image1: Schematic of board
![Image2](https://github.com/Maitreyee2095/Quick-Fix-Keyboard/blob/main/photos/setup.jpg)
Image2: Final Setup

#### Files
Source code can be found under
* Quick-fix-keyboard.c : Main entry point for the application
* Keypad.c/keypad,h : Functionalities of keypad
* sin_trig.c/sin_trig.h : sine function computation
* test_sin.c/test_sin.h : testing sine function
* analog_out.c /analog_out.h: DMA functionality, TPM1 initialization
* DAC.c/DAC.h : Dac functionality
* Circular_buffer.c/Circular_buffer.h : Circular buffer implementation for UART
* test_cbfifo.c/test_cbfifo.h : Testing circular buffer for UART.
* UART.c/Uart.h : Implementation of UART driver
* Command_logger.c/Command_logger.h : function to accept commands from user
* Command_process.c/Command_process.h : Proccesing commands that user input
* jinglebells.c/jinglebells.h : Function to play tune jingle bells
* rabta.c/rabta.h : Function to play song rabta
* piyu_bole.c/piyu_bole.h : Function to play song piyu bole

#### Reference and Credits

The code from earlier assignment was used with certain changes, like implementation of comand handler table and changes in sys_write and sys_read function as suggested by Prof Howdy Pierce in his lecture series.

Would also like to thank Alex Fritz for providing me the speaker, and push buttons to build the piano


