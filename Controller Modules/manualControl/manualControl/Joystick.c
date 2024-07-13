/*
 * Joystick.c
 *
 * Created: 7/7/2024 11:50:30 AM
 *  Author: Konnor Kinnaman
 *
 *	This module handles the use of an analog joystick to control
 *	the speed of the propellers. ADC is initialized with prescalar
 *	of 128. The channel of the joystick y value (0) is passed into
 *	ADC Multiplexer with a safety mask and the result is returned
 *	as a 10 bit number.
 *
 *	OCCUPIES PINS: PC0
 */ 

#include "Joystick.h"

void init_ADC()
{
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	
}

uint16_t read_ADC(uint8_t channel)
{
	uint16_t result;
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);	//Use ADC channel with safety masking
	ADCSRA |= (1<<ADSC);
	
	while (ADCSRA & (1<<ADSC));
	result = ADC;
	
	return result;
}