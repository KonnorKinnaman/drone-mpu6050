/*
 * Joystick.h
 *
 * Created: 7/7/2024 11:50:46 AM
 *  Author: Konnor Kinnaman
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#define F_CPU = 16000000UL

#include <avr/io.h>



//Function Prototypes
void init_ADC(void);
uint16_t read_ADC(uint8_t channel);


#endif /* JOYSTICK_H_ */