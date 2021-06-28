/*
 * B3.c
 *
 * Created: 3-2-2021 14:40:16
 * Author : woute
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms) {
	for(int i = 0; i < ms ; i++){
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0xFF;
	char lichteffect[] = {
		0B00000001,
		0B00000011,
		0B00000111,
		0B00001111,
		0B00011111,
		0B00111111,
		0B01111111,
		0B11111111,
		0B11111110,
		0B11111100,
		0B11111000,
		0B11110000,
		0B11100000,
		0B11000000,
		0B10000000,
		0B00011000,
		0B00100100,
		0B01000010,
		0B10000001,
		0B01000010,
		0B00100100,
		0B00011000
	};
    /* Replace with your application code */
    while (1) 
    {
		for(int i = 0; i < sizeof(lichteffect); i++){
			PORTD = lichteffect[i];
			wait(100);
		}
    }
}

