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


void USART_int_transmit(uint16_t data)
{
	int nDigits = log10(data)+1;
	int numParser;
	char transmit_buffer[10];
	
	//Break data into 'digits' and store each digit as it's ASCII equivalent value
	for (int i = nDigits; i > 0; i--)
	{
		numParser = data % 10;
		data = data / 10;
		transmit_buffer[i] = numParser + '0';	//Convert Decimal to ASCII
	}
	
	//Transmit data
	for (int i = 1; i < nDigits+1; i++)
	{
		while ((UCSR0A & (1<<UDRE0))==0);	//wait for flag to be set
		UDR0 = transmit_buffer[i];
	}
	while ((UCSR0A & (1<<UDRE0))==0);	//wait for flag to be set
	UDR0 = 0x0A;	//New Line
}

void USART_char_transmit(const char *buffer)
{
	while(*buffer)
	{
		while((UCSR0A & (1<<UDRE0)) == 0); //wait for flag to be set
		UDR0 = *buffer; //set UDR0 to character
		buffer++;
	}
	while((UCSR0A & (1<<UDRE0)) == 0); //wait for flag to be set
	UDR0 = 0x0A;
}

void USART_hex_transmit(uint16_t data)
{
	//Convert int to hex - WIP
	char HexReference[] = "0123456789abcdef";
	char hex_data = 0;
	/*while(data--)
	{
		*hex_data++ = HexReference[]
	}*/
	
}