//-----------------------------------------------------------------------------
//
//  USART.h
//
//  Swallowtail USART Firmware for ATmega328P
//  AVR (ATmega328P) USART Firmware
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

#ifndef F_CPU
#define F_CPU 16000000UL //Set clock speed to 16MHz
#endif

#include "USART.h"

/******************* Globals *****************************/


/******************** Functions **************************/

//Function for setting up the USART communication for the ATmega328P
void USART_Init(uint16_t baud){
	//Set-up pinout
	DDR_USART |= (1<<TX) | (0<<RX);
	//Set the default values for outputs to zero and inputs to have pull-up resistors
	PORT_USART |= (0<<TX) | (0<<RX);
	//Set the baud rate
	baud = (F_CPU/(16UL*baud))-1;
	UBRR0H = (uint16_t) (baud>>8);
	UBRR0L = (uint16_t)baud;
	//Enable the receiver and transmitter
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	//Set-up the frame format for the USART communication (8-bits 1 stop bit Parity Disabled)
	UCSR0C |= (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
	return; //Go back to previous location
}

//Function to empty the USART Receiver and Transmit Buffer
uint8_t USART_Flush(){
	unsigned char dummy = 0x00; //Dummy variable to clear the buffer with
	//Check if the RXC0 flag is cleared
	while(UCSR0A & (1<<RXC0)){
		dummy = UDR0; //Flush the FIFO buffer
	}
	return dummy; //Go back to previous location
}

//Function to read the UDR0 Buffer from the receive
unsigned char USART_Read(){
	//Wait for data to be received
	while(!(UCSR0A & (1<<RXC0)));
	//Return received data from the buffer
	return UDR0; //Go back to previous location
}

//Function to write to the UDR0 buffer out
void USART_Write(char data){
	//Wait until the buffer is clear
	while(!(UCSR0A & (1<<UDRE0)));
	//Write the data to the buffer
	UDR0 = data;
	return; //Go back to call point
}


//Write a string to the output
void USART_WriteString(char *data){
	while(*data != '\0'){
		USART_Write(*data);
		++data;
	}
	return; //Go back to call point
}

/******************** Interrupt Service Routines *********/
