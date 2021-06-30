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
	int temp = 0b10000000;
    /* Replace with your application code */
    while (1) 
    {
		PORTD = temp;
		temp = temp >> 1;
		wait(50);
		if(temp == 0){
			temp = 0b10000000;
		}
    }
}

