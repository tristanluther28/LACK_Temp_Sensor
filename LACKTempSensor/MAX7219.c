//-----------------------------------------------------------------------------
//
//  MAX7219.c
//
//  Swallowtail MAX7219 Firmware
//  AVR MAX7219 Firmware
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

#include "MAX7219.h"

/******************* Globals *****************************/


/******************** Functions **************************/

//Initialize Serial Communication and driver settings
void MAX7219_Init(){
	//Initialize the serial comms
	SPI_Init();
	//Decode mode to "Font Code-B"
	MAX7219_Write(MAX7219_MODE_DECODE, 0xFF);
	//Scan limit runs from 0. Set scan to 4-1 to cover the 4 digits
	MAX7219_Write(MAX7219_MODE_SCAN_LIMIT, 0x03);
	//LED Intensity to 8
	MAX7219_Write(MAX7219_MODE_INTENSITY, 0x08);
	//Power on the output display
	MAX7219_Write(MAX7219_MODE_POWER, ON);
	return; //Return to call point
}

//Collect the current temp from the sensor, scale appropriately and return in specified units
void MAX7219_Write(uint8_t reg, uint8_t data){
	//Enable the SPI line
	SPI_Enable();
	//Send the register to write to
	SPI_Transfer(reg);
	//Send the data to put in the register
	SPI_Transfer(data);
	//Disable the SPI line
	SPI_Disable();
	return;
}

//Clear the outputs on the MAX7219
void MAX7219_Clear(){
	//Loop through the scan and send a blank
	int i = 0; //Iterator
	for(i = 0; i < 3; i++){
		MAX7219_Write(i, MAX7219_CHAR_BLANK);
	}
	return;
}

//Write the number passed to this function to the seven segment output. Expecting a number 0.0 - 999.9
void MAX7219_Display4Digit(uint16_t number){
	//Clear the display
	MAX7219_Clear();
	//Get the hundreds place if applicable
	uint8_t hundreds = ((number / 1000) % 10);
	//Get the tens place
	uint8_t tens = ((number / 100) % 10);
	//Get the ones place
	uint8_t ones = ((number / 10) % 10);
	//Get the tens decimal
	uint8_t tens_d = ((number / 1) % 10);
	//Push those numbers to their respective places on the display
	if(hundreds == 0){
		//If the hundreds is zero then print a blank
		MAX7219_Write(MAX7219_DIGIT3, MAX7219_CHAR_BLANK);
	}
	else{
		//Otherwise show it
		MAX7219_Write(MAX7219_DIGIT3, hundreds);
	}
	if(tens == 0 && hundreds == 0){
		//If the tens is zero as well as the hundreds then print a blank
		MAX7219_Write(MAX7219_DIGIT2, MAX7219_CHAR_BLANK);
	}
	else{
		//Otherwise show it
		MAX7219_Write(MAX7219_DIGIT2, tens);
	}
	MAX7219_Write(MAX7219_DIGIT1, ones);
	MAX7219_Write(MAX7219_DIGIT0, tens_d);
	
	return; //Return to call point
}

/******************** Interrupt Service Routines *********/
