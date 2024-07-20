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
#include "Joystick.h"
#include "nRF24l01.h"
#define F_CPU 16000000UL
#define JOYSTICK_Y 0

void init_ALL(void);
void collect_mpu_data(uint16_t *mpu_data);
void collect_joystick_data(void);

int main(void)
{
	init_ALL();
	uint16_t mpu_data[4];
	uint16_t joystick_y;
	
	//Kalman Filter Constants Assuming Level Take-Off Plane and Std Dev of 2 Degrees
	float K_AngleRoll=0, K_UncAngleRoll = 2 * 2;
	float K_AnglePitch = 0, K_UncAnglePitch = 2 * 2;
	float K1DFilterOutput[] = {0,0};	//{angle_prediction, uncertainty_of_prediction}
	float testVal2 = 65.879;
	uint8_t address = 0;
	
	init_nRF();
    
    while (1) 
    {
		//collect_mpu_data();
		//filterOuptut()
		//USART_char_transmit("Data");
		//USART_float_transmit(mpu_data[0], 4, NEWLINE);
		//USART_int_transmit(gy);
		//USART_char_transmit("Accelerometer Output");
		//USART_int_transmit(ax);
		//USART_int_transmit(ay);
		
		/*
		joystick_y = read_ADC(JOYSTICK_Y);
		USART_char_transmit("Joystick Data", NEWLINE);
		if (joystick_y == 520)
		{
			USART_char_transmit("Neutral", NEWLINE);
		}
		else if (520 < joystick_y < 760)
		{
			USART_char_transmit("Half Throttle", NEWLINE);
		}
		else if (761 < joystick_y < 1024)
		{
			USART_char_transmit("Full Throttle", NEWLINE);
		}
		USART_int_transmit(joystick_y);
		_delay_ms(800);
		
		_delay_ms(100); */
		
		
    }
}

void init_ALL(void)
{
	//init_USART();
	init_I2C();
	mpu6050_init();
	init_ADC();
	SPI_init();
}

void collect_mpu_data(uint16_t *mpu_data)
{
	uint16_t gx, gy;
	uint16_t ax, ay;
	float gyro_x_deg, gyro_y_deg;
	
	mpu6050_read_gyro_x(&gx);
	mpu6050_read_gyro_y(&gy);
	gyro_x_deg = gx/131.0;
	gyro_y_deg = gy/131.0;
	
	mpu_data[0,1] = gyro_x_deg, gyro_y_deg;
	
	mpu6050_read_accel_x(&ax);
	mpu6050_read_accel_y(&ay);
	
	mpu_data[2,3] = ax, ay;
}

