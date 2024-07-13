/*
 * sw_sbus.h
 *
 * Created: 7/13/2024 4:51:24 PM
 *  Author: Konnor Kinnaman
 */ 


#ifndef SW_SBUS_H_
#define SW_SBUS_H_

#include <avr/io.h>
#include <util/delay.h>
#include <UART.h>

#define F_CPU 16000000UL

void transmit_sbus_frame(uint16_t* channels);


#endif /* SW_SBUS_H_ */