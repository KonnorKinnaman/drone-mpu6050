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

uint8_t I2C_start(void)
{
	TWCR = START;
	while(!(TWCR & (1<<TWINT)));
	
	uint8_t status = TWSR & 0xF8;
	if (status != 0x08 && status != 0x10)
	{
		return 0;
	}
	return 1;
}

uint8_t I2C_write(uint8_t data)
{
	//Write to I2C device
	TWDR = data;
	TWCR = CLEAR;
	
	while(!(TWCR & (1<<TWINT)));
	
	uint8_t status = TWSR & 0xF8;
	if (status != 0x18 && status != 0x28)
	{
		return 0;
	}
	return 1;
}

uint8_t I2C_read_ACK(void)
{
	//Device Acknowledged
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}

uint8_t I2C_read_NACK(void)
{
	//Device not Acknowledged
	TWCR = (1<<TWEN)|(1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}

void I2C_stop(void)
{
	//Stop I2C Communication
	TWCR = STOP;
	while(TWCR & (1<<TWSTO));
}

void mpu6050_init(void)
{
	//Initialize mpu6050
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);	//Send address with write bit
	I2C_write(0x6B);	//Access PWR_MGMT_1 register
	I2C_write(0x00);	//Start mpu6050 module
	I2C_stop();
}

void mpu6050_read_gyro_x(int8_t *gx)
{
	int8_t gyro_xh;
	int8_t gyro_xl;
	
	//Read from upper GYRO_X register
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);	//Send address with write bit
	I2C_write(GYRO_XOUT_H);	
	I2C_start();
	I2C_write((MPU6050_ADDR << 1) | 1);	
	gyro_xh = ((int8_t)I2C_read_ACK() << 8 | I2C_read_NACK());
	I2C_stop();
	
	//Read from lower GYRO_X register
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);
	I2C_write(GYRO_XOUT_L);
	I2C_start();
	I2C_write((MPU6050_ADDR << 1) | 1);
	gyro_xl = ((int8_t)I2C_read_ACK() << 8 | I2C_read_NACK());
	//*gy = ((int16_t)I2C_read_ACK() << 8 | I2C_read_ACK());
	//*gz = ((int16_t)I2C_read_ACK() << 8 | I2C_read_NACK());
	*gx = (gyro_xh << 8) | gyro_xl ;
	I2C_stop();
	
}

void mpu6050_read_gyro_y(int16_t *gy)
{
	int8_t gyro_yh;
	int8_t gyro_yl;
	
	//Read from upper GYRO_Y register
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);
	I2C_write(GYRO_YOUT_H);
	I2C_start();
	I2C_write((MPU6050_ADDR << 1) | 1);
	gyro_yh = ((int8_t)I2C_read_ACK()<< 8 | I2C_read_NACK());
	I2C_stop();
	
	//Read from lower GYRO_Y register
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);
	I2C_write(GYRO_YOUT_L);
	I2C_start();
	I2C_write((MPU6050_ADDR << 1) | 1);
	gyro_yl = ((int8_t)I2C_read_ACK() << 8 | I2C_read_NACK());
	I2C_stop();
	
	*gy = (gyro_yh << 8) | gyro_yl;
}

void mpu6050_read_accel_x(int16_t *ax)
{
	int8_t accel_xh;
	int8_t accel_xl;
	
	//Read from upper ACCEL_X register
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);
	I2C_write(ACCEL_XOUT_H);
	I2C_start();
	I2C_write((MPU6050_ADDR << 1) | 1);
	accel_xh = ((int8_t)I2C_read_ACK() << 8 | I2C_read_NACK());
	I2C_stop();
	
	//Read from lower ACCEL_X register
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);
	I2C_write(ACCEL_XOUT_L);
	I2C_start();
	I2C_write((MPU6050_ADDR << 1) | 1);
	accel_xl = ((int8_t)I2C_read_ACK() << 8 | I2C_read_NACK());
	I2C_stop();
	
	*ax = (accel_xh << 8) | accel_xl;
}

void mpu6050_read_accel_y(int16_t *ay)
{
	int8_t accel_yh;
	int8_t accel_yl;
	
	//Read from upper ACCEL_Y register
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);
	I2C_write(ACCEL_YOUT_H);
	I2C_start();
	I2C_write((MPU6050_ADDR << 1) | 1);
	accel_yh = ((int8_t)I2C_read_ACK() << 8 | I2C_read_NACK());
	I2C_stop();
	
	//Read from lower ACCEL_Y register
	I2C_start();
	I2C_write(MPU6050_ADDR << 1);
	I2C_write(ACCEL_YOUT_L);
	I2C_start();
	I2C_write((MPU6050_ADDR << 1) | 1);
	accel_yl = ((int8_t)I2C_read_ACK() << 8 | I2C_read_NACK());
	I2C_stop();
	
	*ay = (accel_yh << 8) | accel_yl;
}

void filterOuptut(float KalmanState, float KalmanUnc, float KalmanInput,  float KalmanMeas, const float *KFilterOut)
{
	float KalmanGain;
	KalmanState = KalmanState + 0.004 * KalmanInput;
	KalmanUnc = KalmanUnc + 0.004 * 0.004 * 4 * 4;
	
	float KalmanGain = KalmanUnc * 1/(1*KalmanUnc + 3 * 3);
	KalmanState = KalmanState + KalmanGain * (KalmanMeas - KalmanState);
	KalmanUnc = (1-KalmanGain) * KalmanUnc;
	
	*KFilterOut[0] = KalmanState;
	*KFilterOut[1] = KalmanUnc;
}