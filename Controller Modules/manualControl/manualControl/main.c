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
//#include "serial.c"
#define F_CPU 16000000UL

void init_ALL(void);

int main(void)
{
	init_ALL();
	int received_data = 0;
	int16_t gx, gy;
	int16_t ax, ay;
	float gyro_x_deg, gyro_y_deg;
	
	//Kalman Filter Constants Assuming Level Take-Off Plane and Std Dev of 2 Degrees
	float K_AngleRoll=0, K_UncAngleRoll = 2 * 2;
	float K_AnglePitch = 0, K_UncAnglePitch = 2 * 2;
	float K1DFilterOutput[] = {0,0};	//{angle_prediction, uncertainty_of_prediction}
	float testVal2 = 65.879;
	uint8_t address = 0;
    
    while (1) 
    {
		
		mpu6050_read_gyro_x(&gx);
		mpu6050_read_gyro_y(&gy);
		mpu6050_read_accel_x(&ax);
		mpu6050_read_accel_y(&ay);
		gyro_x_deg = gx/131.0;
		int8_t scaled_x = gx/2;
		
		USART_char_transmit("Gyroscope Output");
		USART_float_transmit(gyro_x_deg, 2);
		USART_int_transmit(gy);
		USART_char_transmit("Accelerometer Output");
		USART_int_transmit(ax);
		USART_int_transmit(ay);
		_delay_ms(1000);
    }
}

void init_ALL(void)
{
	//init_USART();
	init_I2C();
	mpu6050_init();
}

