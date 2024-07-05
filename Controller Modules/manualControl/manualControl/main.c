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
	int16_t gx, gy, gz;
	uint16_t testVal2 = 65.879;
	uint8_t address = 0;
    
	//address = I2C_scan();
    while (1) 
    {
		
		mpu6050_read_gyro(&gx, &gy, &gz);
		USART_int_transmit(gx);
		//USART_int_transmit(gy);
		//USART_int_transmit(gz);
		_delay_ms(1000);
    }
}

void init_ALL(void)
{
	init_USART();
	init_I2C();
	mpu6050_init();
}

