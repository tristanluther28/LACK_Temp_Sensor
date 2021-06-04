//-----------------------------------------------------------------------------
//
//  ADC.c
//
//  Swallowtail ADC Firmware
//  AVR ADC Firmware
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

#include "ADC.h"

/******************* Globals *****************************/


/******************** Functions **************************/

//Initialize the ADC
void ADC_Init(){
	//Use VCC for the analog reference voltage, right justify result, only use ADC0 for input
	ADMUX = (0<<REFS1)|(0<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	//Enable ADC, use for single conversion mode, clk/8 prescaler
	ADCSRA = (1<<ADEN)|(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	return; //Return to call point
}

//Reads the value from the ADC
uint16_t ADC_Value(){
	//Pass bit in to get request measurement
	ADCSRA |= (1<<ADSC);
	//Wait for conversion
	while(BIT_SET(ADCSRA, ADSC));
	//Return the 10-bit right justified result
	return ADC;
}

/******************** Interrupt Service Routines *********/
