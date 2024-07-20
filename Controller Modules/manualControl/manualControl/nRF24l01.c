/*
 * nRF24l01.c
 *
 * Created: 7/11/2024 11:21:05 AM
 *  Author: Konnor Kinnaman
 *
 * OCCUPIES PINS: PB2 (SS), PB3 (MOSI), PB4 (MISO), PB5 (SCK), PC3 (CE)
 */ 

#include "nRF24l01.h"
#include "UART.h"

void SPI_init(void)
{
	DDRB = (1<<DDB3) | (1<<DDB5);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

int SPI_transmit(uint8_t data)
{
	uint8_t iteration = 0;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)))
	{
		USART_char_transmit("Waiting for data to send", NEWLINE);
		if (iteration == 10)
		{
			USART_char_transmit("Failed to transmit data after 10 tries - Exiting", NEWLINE);
			return 0;
		}
		iteration++;
	}
	
	SPSR &= ~(1<<SPIF);
}

uint8_t SPI_receive(void)
{
	uint8_t data;
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	SPSR &= ~(1<<SPIF);
	return SPDR;
}

uint8_t conf_CSN(uint8_t mode)
{
	if (mode == SELECT)
	{
		PORTB &= ~(1<<CSN); //Select nRF24L01
		USART_char_transmit("nRF Selected", NEWLINE);
	}
	else if (mode == DESELECT)
	{
		PORTB |= (1<<CSN); //Deselect nRF24L01
		USART_char_transmit("nRF Deselected", NEWLINE);
	}
	else 
	{
		USART_char_transmit("Invalid Mode Arg - nRF in ambiguous state", NEWLINE);
		return 0;
	}
	return 1;
}

void init_nRF(void)
{
	uint8_t status;
	status = conf_CSN(SELECT);
	if (status == 0)
	{
		USART_char_transmit("Init Failed with Error status S0", NEWLINE);
		return status;
	}
	status = SPI_transmit((W_REGISTER) << 5 | NRF_CONFIG);
	if (status == 0)
	{
		return 0;
	}
	SPI_transmit(1 << PWR_UP);
	if (status == 0)
	{
		return 0;
	}
	
	status = conf_CSN(DESELECT);
	if (status == 0)
	{
		USART_char_transmit("Init Failed with Error status DS0", NEWLINE);
		return status;
	}
	
}

void wireless_Transmit(void);

void wireless_Read(uint8_t regist)
{
	
}