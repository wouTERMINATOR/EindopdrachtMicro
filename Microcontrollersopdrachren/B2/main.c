/*
 * Microcontrollersopdrachren.c
 *
 * Created: 3-2-2021 14:36:38
 * Author : woute
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8e6

void wait( int ms) {
	for(int i = 0; i < ms ; i++){
		_delay_ms(1);
	}
}


int main(void)
{
	DDRD = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		PORTD = 0b10000000;
		wait(500);
		PORTD = 0b01000000;
		wait(500);
    }
}

