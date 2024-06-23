/*
 * uC test.c
 *
 * Created: 3/1/2024 3:47:20 PM
 * Author : Konnor Kinnaman
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void init_IO(void);
int main(void)
{
    init_IO();
    while (1) 
    {
		PORTD = 0xFF;
		_delay_ms(5000);
		PORTD = 0x00;
		_delay_ms(5000);
    }
}

void init_IO()
{
	DDRD = 0xFF;
	PORTD = 0x00;	//PORTD -> Output
}

