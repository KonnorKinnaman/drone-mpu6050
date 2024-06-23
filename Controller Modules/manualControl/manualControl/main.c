/*
 * manualControl.c
 *
 * Created: 6/23/2024 2:00:47 PM
 * Author : Konnor Kinnaman
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "UART.h"
#define F_CPU 16000000UL

void init_ALL(void);

int main(void)
{
	
	uint8_t testVal2 = 75;
	//float testVal = 135.467;
    
    while (1) 
    {
		USART_transmit(testVal2);
    }
}

void init_ALL(void)
{
	init_USART();
}

