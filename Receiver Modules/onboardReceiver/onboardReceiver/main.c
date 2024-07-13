/*
 * onboardReceiver.c
 *
 * Created: 7/13/2024 4:25:32 PM
 * Author : Konnor Kinnaman
 */ 

#include <avr/io.h>
#include <sw_sbus.h>

#define F_CPU 16000000UL

void init_ALL(void);

int main(void)
{
	uint16_t channels[16] = {
		1024, 1024, 1024, 1024, // Channel 1-4
		1024, 1024, 1024, 1024, // Channel 5-8
		1024, 1024, 1024, 1024, // Channel 9-12
		1024, 1024, 1024, 1024  // Channel 13-16
	};
    
    while (1) 
    {
		transmit_sbus_frame(&channels);
		
		_delay_ms(14);
    }
}

void init_ALL(void)
{
	init_USART();
}

