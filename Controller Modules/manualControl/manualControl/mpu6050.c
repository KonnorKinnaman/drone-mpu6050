/*
 * mpu6050.c
 *
 * Created: 6/25/2024 10:25:01 PM
 *  Author: Konnor Kinnaman
 */ 
#include "mpu6050.h"

void init_I2C(void)
{
	DDRC &= ~((1<<DDC4) | (1<<DDC5));
	PORTC |= (1<<PORTC4) | (1<<PORTC5);
	
	TWSR = 0x00; //Prescalar of 1
	TWBR = ((F_CPU/SCL_CLOCK) - 16) / 2;	//Set Baud Rate for Transmission
}

uint8_t I2C_scan(void)
{
	//Scan all possible address for slave device
	for (uint8_t address = 1; address < 128; address++)
	{
		TWCR = START;
		while (!(TWCR & (1<<TWINT)));
		
		while (TWSR != 0x08)
		{
			USART_char_transmit("Start condition not transmitted");
		}
		
		TWDR = (address<<1);
		TWCR = CLEAR;
		while(!(TWCR & (1<<TWINT)));
		
		if (TWSR == 0x18 || TWSR == 0x40)
		{
			USART_char_transmit("Device Found at:");
			USART_int_transmit(address);
			return address;
		}
		TWCR = STOP;
	}
	USART_char_transmit("No Devices Found");
	return 0;
}

uint16_t I2C_recieve(uint8_t address)
{
	int data = 0;
	TWCR = START;
	while (!(TWCR & (1<<TWINT)))
	{
		USART_char_transmit("Waiting for Acknowledgment of START");
	}
	USART_char_transmit("START Acknowledged");
	while (TWSR != 0x08)
	{
		uint16_t error = 0;
		USART_char_transmit("An Error Occurred While Initializing I2C");
		USART_char_transmit("Expected 08 but got the following:");
		error = TWSR;
		USART_int_transmit(error);
		_delay_ms(1000);
		
	}
	USART_char_transmit("I2C Initialization Successful");
	TWCR = CLEAR;
	TWDR = ((address<<1) | PORTC4);
	while (!(TWCR & (1<< TWINT)));
	
	if (TWSR == 0x38)
	{
		USART_char_transmit("Arbitration Lost");
	}
	else if (TWSR == 0x40)
	{
		USART_char_transmit("Mode Transmitted: Master Receive Mode. Device Acknowledged");
		data = TWDR*100;
	}
	else if (TWSR == 0x48)
	{
		USART_char_transmit("No Acknowledgment from Device: Attempting to Fix");
		data = TWDR*100;
		
	}
	else
	{
		USART_char_transmit("Did not register valid status code!");
		USART_char_transmit("Expected 38, 40, or 48, but received the following:");
		USART_int_transmit(TWSR);
		
	}
	TWCR = STOP;
	return data;
}