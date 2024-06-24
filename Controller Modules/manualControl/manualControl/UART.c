/*
 * UART.c
 *
 * Created: 6/23/2024 2:01:30 PM
 *  Author: Konnor Kinnaman
 */ 

#include "UART.h"

void init_USART(void)
{
	UCSR0A = 0x00;	//Clear Register
	UCSR0B = (1<<TXEN0);	//Enable transmit
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);	//8 bit character size, stop bits 1
	uint16_t ubbr = (F_CPU)/(16UL * baud) - 1;
	UBRR0H = (ubbr>>8) & 0x0F;	//Set upper ubbr to 0
	UBRR0L = ubbr;
}


void USART_transmit(uint32_t data)
{
	int nDigits = log10(data)+1;
	uint8_t transmit_buffer[10];
	sprintf(transmit_buffer, "%d", data);
	for (int i = 0; i < nDigits; i++)
	{
		while ((UCSR0A & (1<<UDRE0))==0);	//wait for flag to be set
		UDR0 = transmit_buffer[i];
	}
	while ((UCSR0A & (1<<UDRE0))==0);	//wait for flag to be set
	UDR0 = 0x0A;	//New Line
}