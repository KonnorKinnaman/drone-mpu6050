/*
 * mpu6050.h
 *
 * Created: 6/25/2024 10:25:18 PM
 *  Author: Konnor Kinnaman
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

//Definitions
#define F_CPU 16000000UL
#define SCL_CLOCK 100000L

#define START (1<<TWINT)|(1<<TWSTA)|(0<<TWSTO)|(1<<TWEN)
#define R_START (1<<TWINT)|(1<<TWSTA)|(0<<TWSTO)|(1<<TWEN)
#define STOP (1<<TWINT)|(0<<TWSTA)|(1<<TWSTO)|(1<<TWEN)
#define CLEAR (1<<TWINT)|(0<<TWSTA)|(0<<TWSTO)|(1<<TWEN)
#define MPU6050_ADDR 0x68
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E

//Function Prototypes
void init_I2C(void);
uint8_t I2C_start(void);
void I2C_stop(void);
uint8_t I2C_write(uint8_t data);
uint8_t I2C_read_ACK(void);
uint8_t I2C_read_NACK(void);

void mpu6050_init(void);
void mpu6050_read_gyro_x(uint16_t *gx);
void mpu6050_read_gyro_y(uint16_t *gy);
void mpu6050_read_accel_x(uint16_t *ax);
void mpu6050_read_accel_y(uint16_t *ay);

void filterOuptut(float KalmanState, float KalmanUnc, float KalmanInput,  float KalmanMeas, float *KFilterOut);



#endif /* MPU6050_H_ */