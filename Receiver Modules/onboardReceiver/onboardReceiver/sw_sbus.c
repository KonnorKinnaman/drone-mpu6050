/*
 * sw_sbus.c
 *
 * Created: 7/13/2024 4:51:09 PM
 *  Author: Konnor Kinnaman
 */ 

#include <sw_sbus.h>

void init_USART(void)
{
	UCSR0A = 0x00;	//Clear Register
	UCSR0B = (1<<TXEN0);	//Enable transmit
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);	//8 bit character size, stop bits 1
	uint16_t ubbr = (F_CPU)/(16UL * baud) - 1;
	UBRR0H = (ubbr>>8) & 0x0F;	//Set upper ubbr to 0
	UBRR0L = ubbr;
}

void USART_int_transmit(uint8_t data)
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

void transmit_sbus_frame(uint16_t* channels)
{
	uint8_t sbusFrame[25];
	
	// Start byte
	sbusFrame[0] = 0x0F;
	
	// 16 channels data (22 bytes)
	sbusFrame[1] = (channels[0] & 0x07FF);
	sbusFrame[2] = (channels[0] >> 8) | ((channels[1] & 0x001F) << 3);
	sbusFrame[3] = (channels[1] >> 5) | ((channels[2] & 0x0003) << 6);
	sbusFrame[4] = (channels[2] >> 2) & 0x00FF;
	sbusFrame[5] = (channels[2] >> 10) | ((channels[3] & 0x00FF) << 1);
	sbusFrame[6] = (channels[3] >> 7) | ((channels[4] & 0x000F) << 4);
	sbusFrame[7] = (channels[4] >> 4) | ((channels[5] & 0x0001) << 7);
	sbusFrame[8] = (channels[5] >> 1) & 0x00FF;
	sbusFrame[9] = (channels[5] >> 9) | ((channels[6] & 0x007F) << 2);
	sbusFrame[10] = (channels[6] >> 6) | ((channels[7] & 0x0007) << 5);
	sbusFrame[11] = (channels[7] >> 3) & 0x00FF;
	sbusFrame[12] = (channels[8] & 0x07FF);
	sbusFrame[13] = (channels[8] >> 8) | ((channels[9] & 0x001F) << 3);
	sbusFrame[14] = (channels[9] >> 5) | ((channels[10] & 0x0003) << 6);
	sbusFrame[15] = (channels[10] >> 2) & 0x00FF;
	sbusFrame[16] = (channels[10] >> 10) | ((channels[11] & 0x00FF) << 1);
	sbusFrame[17] = (channels[11] >> 7) | ((channels[12] & 0x000F) << 4);
	sbusFrame[18] = (channels[12] >> 4) | ((channels[13] & 0x0001) << 7);
	sbusFrame[19] = (channels[13] >> 1) & 0x00FF;
	sbusFrame[20] = (channels[13] >> 9) | ((channels[14] & 0x007F) << 2);
	sbusFrame[21] = (channels[14] >> 6) | ((channels[15] & 0x0007) << 5);
	sbusFrame[22] = (channels[15] >> 3) & 0x00FF;
	
	sbusFrame[23] = 0x00; //Use for failsafe
	
	sbusFrame[24] = 0x00; //End byte
	
	for (uint8_t i = 0; i < 25; i++) {
		USART_int_transmit(sbusFrame[i]);
	}
}