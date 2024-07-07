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
	//Exception handler for 0
	if (data == 0)
	{
		while ((UCSR0A & (1<<UDRE0))==0);
		UDR0 = 0x30;
	}
	else
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
	}
	while ((UCSR0A & (1<<UDRE0))==0);	//wait for flag to be set
	UDR0 = 0x0A;	//New Line
}

void USART_char_transmit(const char *buffer, int mode)
{
	if (mode == NULL)
	{
		mode = NONE;
	}
	
	if (mode == LOGGING)
	{
		while((UCSR0A & (1<<UDRE0)) == 0); //wait for flag to be set
		UDR0 = 0x1B;
	}
	while(*buffer)
	{
		while((UCSR0A & (1<<UDRE0)) == 0); //wait for flag to be set
		UDR0 = *buffer; //set UDR0 to character
		buffer++;
	}
	if (1)
	{
		while((UCSR0A & (1<<UDRE0)) == 0); //wait for flag to be set
		UDR0 = 0x0A;	
	}
}

void USART_float_transmit(float input, int decimals, int mode)
{
	int digit;
	char buffer[10];
	int integer = (int)input;
	float fraction = input - integer;
	sprintf(buffer, "%d.", integer);
	
	for(int i = 0; i < decimals; i++)
	{
		fraction *= 10;
		int digit = (int)fraction;
		sprintf(buffer +strlen(buffer), "%d", digit);
		fraction -= digit;
	}
	
	USART_char_transmit(buffer, mode);
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