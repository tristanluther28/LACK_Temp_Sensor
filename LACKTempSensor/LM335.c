//-----------------------------------------------------------------------------
//
//  LM335.c
//
//  Swallowtail LM335 Firmware
//  AVR LM335 Firmware
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

#include "LM335.h"

/******************* Globals *****************************/


/******************** Functions **************************/

//Initialize ADC that this sensor relies on
void LM335_Init(){
	//Initialize the output 
	ADC_Init();
	return; //Return to call point
}

//Collect the current temp from the sensor, scale appropriately and return in specified units
float LM335_Read(enum tempunits units){
	float value;
	//Get the current value from the 10-bit ADC
	uint16_t raw_value = ADC_Value();
	raw_value = 1024 - raw_value; //Get the reverse of the range of numbers
	//Return in the specified units
	switch(units){
		case KELVIN:
			value = raw_value * 0.4882;
			return value;
		break;
		case CELSUIS:
			value = (raw_value * 0.4882) - 273.15;
			return value;
		break;
		case FAHRENHEIT:
			value = (((raw_value * 0.4882) - 273.15) * 1.8) + 32;
			return value;
		break;
	}
	//Invalid enum passed, return raw_adc value
	return (float)raw_value;
}

/******************** Interrupt Service Routines *********/
