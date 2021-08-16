//-----------------------------------------------------------------------------
//
//  LTC4627JS.c
//
//  Swallowtail LTC4627JS using 74HC138 Firmware
//  AVR LTC4627JS using 74HC138 Firmware
//
//  Copyright (c) 2021 Swallowtail Electronics
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sub-license,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//  Web:    http://tristanluther.com
//  Email:  tristanluther28@gmail.com
//
//-----------------------------------------------------------------------------

/******************** Includes ***************************/

#include "LTC4627JS.h"

/******************* Globals *****************************/


/******************** Functions **************************/

//Initialize the GPIO for PMOS sinks and 74HC138
void LTC4627JS_Init(){
	//Init PWM for display brightness
	PWM_Init();
	PWM_timer1_a(40); //Almost full brightness/conserve some power and makes more readable
	//Set all of the 74HC138 GPIO as outputs
	DDR_138 |= (1<<A_138)|(1<<B_138)|(1<<C_138);
	PORT_138 |= (0<<A_138)|(0<<B_138)|(0<<C_138);
	
	//Set all of the Seven Segment GPIO as outputs
	DDR_SEG |= (1<<A_L1)|(1<<B_L2)|(1<<C_L3)|(1<<D)|(1<<E)|(1<<F)|(1<<G)|(1<<DP);
	PORT_SEG |= (0<<A_L1)|(0<<B_L2)|(0<<C_L3)|(0<<D)|(0<<E)|(0<<F)|(0<<G)|(0<<DP);
	return; //Return to call point
}

//Collect the current temp from the sensor, scale appropriately and return in specified units
void LTC4627JS_Write(uint8_t char_num, uint8_t data){
	//Push the data to the seven segment port
	switch(data){
		case 0:
			PORT_SEG = LTC4627JS_ZERO;
			break;
		case 1:
			PORT_SEG = LTC4627JS_ONE;
			break;
		case 2:
			PORT_SEG = LTC4627JS_TWO;
			break;
		case 3:
			PORT_SEG = LTC4627JS_THREE;
			break;
		case 4:
			PORT_SEG = LTC4627JS_FOUR;
			break;
		case 5:
			PORT_SEG = LTC4627JS_FIVE;
			break;
		case 6:
			PORT_SEG = LTC4627JS_SIX;
			break;
		case 7:
			PORT_SEG = LTC4627JS_SEVEN;
			break;
		case 8:
			PORT_SEG = LTC4627JS_EIGHT;
			break;
		case 9:
			PORT_SEG = LTC4627JS_NINE;
			break;
		case LTC4627JS_CHAR_BLANK:
			PORT_SEG = LTC4627JS_CHAR_BLANK;
		break;
		case 10:
			PORT_SEG = LTC4627JS_L3;
		break;
		case 70:
			PORT_SEG = LTC4627JS_F;
		break;
		case 43:
			PORT_SEG = LTC4627JS_C;
		break;
		case 75:
			PORT_SEG = LTC4627JS_K;
		break;
		default:
			PORT_SEG = LTC4627JS_ZERO;
			break;
	}
	//Push the digit info to the 74HC138
	switch(char_num){
		case 0:
			PORT_138 = LTC4627JS_DIGIT0;
			break;
		case 1:
			PORT_138 = LTC4627JS_DIGIT1;
			break;
		case 2:
			PORT_138 = LTC4627JS_DIGIT2;
			break;
		case 3:
			PORT_138 = LTC4627JS_DIGIT3;
			break;
		default:
			PORT_138 = LTC4627JS_L;
			break;
	}
	
	_delay_ms(2);
	return;
}

//Write the number passed to this function to the seven segment output. Expecting a number 0.0 - 999.9
void LTC4627JS_Display4Digit(uint16_t number){
	//Get the thousands place
	uint8_t thousands = ((number / 1000) % 10);
	//Get the hundreds place if applicable
	uint8_t hundreds = ((number / 100) % 10);
	//Get the tens place
	uint8_t tens = ((number / 10) % 10);
	//Get the ones place
	uint8_t ones = ((number / 1) % 10);
	//Push those numbers to their respective places on the display
	if(thousands == 0){
		//If the hundreds is zero then print a blank
		LTC4627JS_Write(0, LTC4627JS_CHAR_BLANK);
	}
	else{
		//Otherwise show it
		LTC4627JS_Write(0, thousands);
	}
	if(hundreds == 0 && thousands == 0){
		//If the tens is zero as well as the hundreds then print a blank
		LTC4627JS_Write(1, LTC4627JS_CHAR_BLANK);
	}
	else{
		//Otherwise show it
		LTC4627JS_Write(1, hundreds);
	}
	if(tens == 0 && hundreds == 0 && thousands == 0){
		//If the tens is zero as well as the hundreds then print a blank
		LTC4627JS_Write(2, LTC4627JS_CHAR_BLANK);
	}
	else{
		//Otherwise show it
		//FORCE A F UNTIL THE LAST DIGIT WORKS
		LTC4627JS_Write(2, tens);
		/*LTC4627JS_Write(2, 70);
		LTC4627JS_Write(5, 10);*/
	}
	LTC4627JS_Write(3, ones);
	
	return; //Return to call point
}

void LTC4627JS_DisplayTemp(uint16_t number, uint8_t units){
	//Get the hundreds place if applicable
	uint8_t hundreds = ((number / 100) % 10);
	//Get the tens place
	uint8_t tens = ((number / 10) % 10);
	//Get the ones place
	uint8_t ones = ((number / 1) % 10);
	//Push those numbers to their respective places on the display
	if(hundreds == 0){
		//If the hundreds is zero then print a blank
		LTC4627JS_Write(0, LTC4627JS_CHAR_BLANK);
	}
	else{
		//Otherwise show it
		LTC4627JS_Write(0, hundreds);
	}
	if(tens == 0 && hundreds == 0){
		//If the tens is zero as well as the hundreds then print a blank
		LTC4627JS_Write(1, LTC4627JS_CHAR_BLANK);
	}
	else{
		//Otherwise show it
		LTC4627JS_Write(1, tens);
	}
	//Otherwise show it
	LTC4627JS_Write(2, ones);
	switch(units){
		case 0:
			LTC4627JS_Write(3, 75);
			break;
		case 1:
			LTC4627JS_Write(3, 43);
			LTC4627JS_Write(5, 10);
			break;
		case 2:
			LTC4627JS_Write(3, 70);
			LTC4627JS_Write(5, 10);
			break;
		default:
			LTC4627JS_Write(3, 70);
			LTC4627JS_Write(5, 10);
			break;
	}
	return; //Return to call point
};

/******************** Interrupt Service Routines *********/
