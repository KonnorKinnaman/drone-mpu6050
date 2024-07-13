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
#include <stdbool.h>
#include <math.h>

//Definitions
#define F_CPU 16000000UL
#define baud 57600

enum mode {
	NEWLINE,
	LOGGING,
	NONE
	};

//Function Prototypes
void init_USART(void);
void USART_int_transmit(uint16_t data);
void USART_char_transmit(const char *buffer, int mode);
void USART_float_transmit(float input, int decimals, int mode);
void USART_hex_transmit(uint8_t data);



#endif /* UART_H_ */