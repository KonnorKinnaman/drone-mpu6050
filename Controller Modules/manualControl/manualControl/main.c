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
#include "mpu6050.h"
#define F_CPU 16000000UL

void init_ALL(void);

int main(void)
{
	
	int received_data = 0;
	uint16_t testVal2 = 65.879;
	uint8_t address = 0;
    
	init_I2C();
	//address = I2C_scan();
    while (1) 
    {
		
		received_data = I2C_recieve(104);
		USART_int_transmit(received_data);
    }
}

void init_ALL(void)
{
	init_USART();
}

