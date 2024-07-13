/*
 * nRF24l01.c
 *
 * Created: 7/11/2024 11:21:05 AM
 *  Author: Konnor Kinnaman
 *
 * OCCUPIES PINS: PB2 (SS), PB3 (MOSI), PB4 (MISO), PB5 (SCK), PC3 (CE)
 */ 

#include "nRF24l01.h"

void SPI_init(void)
{
	DDRB = (1<<DDB3) | (1<<DDB5);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

void SPI_transmit(uint16_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}