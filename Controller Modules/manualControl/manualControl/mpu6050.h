/*
 * mpu6050.h
 *
 * Created: 6/25/2024 10:25:18 PM
 *  Author: Konnor Kinnaman
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_

#include <avr/io.h>

//Definitions
#define F_CPU = 16000000UL

#define START (1<<TWINT)|(1<<TWSTA)|(0<<TWSTO)|(1<<TWEN)
#define R_START (1<<TWINT)|(1<<TWSTA)|(0<<TWSTO)|(1<<TWEN)
#define STOP (1<<TWINT)|(0<<TWSTA)|(1<<TWSTO)|(1<<TWEN)


typedef enum
{
	I2C_NO_ERROR,	//No Error
	I2C_ADDR_NACK,	//Address not acknowledged
	I2C_DATA_NACK,	//Data no acknowledged
	I2C_BUS_COLLISION,	//Bus Collision Error
	I2C_BUSY	//Host is busy
	
}i2c_error_t;

//Function Protos
void init_I2C(void);



#endif /* MPU6050_H_ */