/*
 * manualControl.c
 *
 * Created: 6/23/2024 2:00:47 PM
 * Author : Konnor Kinnaman
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "UART.h"
#define F_CPU 16000000UL

void init_ALL(void);

int main(void)
{
	
	uint32_t testVal2 = 657365;
	//float testVal = 135.467;
    
    while (1) 
    {
		USART_transmit(testVal2);
		//_delay_ms(500);
    }
}

void init_ALL(void)
{
	init_USART();
}

