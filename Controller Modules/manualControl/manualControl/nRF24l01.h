/*
 * nRF24l01.h
 *
 * Created: 7/11/2024 11:21:27 AM
 *  Author: Konnor Kinnaman
 */ 


#ifndef NRF24L01_H_
#define NRF24L01_H_
#include <avr/io.h>

#define F_CPU 16000000UL

#define CONFIG 0x00
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
#define FIFO_STATUS 0x17 


//Function Prototypes
void SPI_init(void);
void SPI_transmit(uint16_t data);



#endif /* NRF24L01_H_ */