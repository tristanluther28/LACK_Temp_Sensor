//-----------------------------------------------------------------------------
//
//  LTC4627JS.h
//
//  Swallowtail LTC4627JS Firmware
//  AVR LTC4627JS Firmware
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

/******************** Include Guard **************************/

#ifndef LTC4627JS_H_
#define LTC4627JS_H_

#ifndef F_CPU
#define F_CPU 1000000UL //Set clock speed to 1MHz
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "PWM.h"

/******************* Macros **********************************/

#define BIT_SET(byte, bit) (byte & (1<<bit))

#define ON                        1
#define OFF                       0

#define LTC4627JS_MODE_INTENSITY    0x0A
#define LTC4627JS_MODE_NOOP         0x00
#define LTC4627JS_CHAR_BLANK        0xFF
#define LTC4627JS_CHAR_NEGATIVE     0xA

//74HC138 Connections
#define DDR_138 DDRC
#define PORT_138 PORTC
#define A_138 PC0
#define B_138 PC2
#define C_138 PC3

#define LTC4627JS_DIGIT0            0x08
#define LTC4627JS_DIGIT1            0x05
#define LTC4627JS_DIGIT2            0x01
#define LTC4627JS_DIGIT3            0x00
#define LTC4627JS_L					0x04

//Seven Segment Connections
#define DDR_SEG DDRD
#define PORT_SEG PORTD
#define A_L1 PD0
#define B_L2 PD1
#define C_L3 PD2
#define D PD3
#define E PD4
#define F PD5
#define G PD6
#define DP PD7
#define LTC4627JS_ONE 0x79
#define LTC4627JS_TWO 0x24
#define LTC4627JS_THREE 0x30
#define LTC4627JS_FOUR 0x19
#define LTC4627JS_FIVE 0x12
#define LTC4627JS_SIX 0x02
#define LTC4627JS_SEVEN 0x78
#define LTC4627JS_EIGHT 0x00
#define LTC4627JS_NINE 0x10
#define LTC4627JS_ZERO 0x40
#define LTC4627JS_C 0x46
#define LTC4627JS_F 0x8E
#define LTC4627JS_K 0x05
#define LTC4627JS_L3 0x03

/******************* Function Declarations *******************/

void LTC4627JS_Init();
void LTC4627JS_Write(uint8_t, uint8_t);
void LTC4627JS_Display4Digit(uint16_t);
void LTC4627JS_DisplayTemp(uint16_t, uint8_t);

#endif