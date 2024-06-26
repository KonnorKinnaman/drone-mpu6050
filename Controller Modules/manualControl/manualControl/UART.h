/*
 * UART.h
 *
 * Created: 6/23/2024 2:01:42 PM
 *  Author: Konnor Kinnaman
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#define F_CPU 16000000UL
#define baud 57600

//Function Prototypes
void init_USART(void);
void USART_transmit(uint16_t data);



#endif /* UART_H_ */