/*
 * B3.c
 *
 * Created: 3-2-2021 14:40:16
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
		if(PINC == 0b00000001){
			PORTD = 0b10000000;
			wait(250);
			PORTD = 0b00000000;
			wait(250);
		} else {
			PORTD = 0b00000000;
		}
    }
}

