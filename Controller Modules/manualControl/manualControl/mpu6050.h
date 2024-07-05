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


typedef enum
{
	I2C_NO_ERROR,	//No Error
	I2C_ADDR_NACK,	//Address not acknowledged
	I2C_DATA_NACK,	//Data no acknowledged
	I2C_BUS_COLLISION,	//Bus Collision Error
	I2C_BUSY	//Host is busy
	
}i2c_error_t;

enum
{
	//START = 0x08,	//Start condition has been sent
	REP_START = 0x10,	//Repeated Start condition has been sent
	ARB_LOST = 0x38,	//Arbitration was lost
	SLAR_ACK_REC = 0x40,	
	SLAR_NACK_REC = 0x48,
	DATA_REC_ACK_RET = 0x50,
	DATA_REC_NACK_RET = 0x58,
	SLAW_ACK_RET = 0x60,
	ARB_LOST_MASTER = 0x68,	//Arbitration lost in SLA+R/W as Master, own SLA+W received, ACK returned
	GEN_CALL = 0x70,
	GEN_CALL_ARB_LOST = 0x78,
	PREV_ADDR = 0x80,
	
	 
}twsr_status_code;

//Function Prototypes
void init_I2C(void);
uint8_t I2C_scan(void);
uint16_t I2C_recieve(uint8_t address);



#endif /* MPU6050_H_ */