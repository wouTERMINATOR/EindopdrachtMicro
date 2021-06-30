/*
 * B3.c
 *
 * Created: 10-2-2021 14:03:08
 * Author : woute
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8e6
// 7 seg
// PORTD dp G F E D C B A
//        y y y y x x x x

char pattern[] = {
	0x3F, 0x30, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0xF7, 0xFF, 0xB9, 0xBF, 0xF9, 0xF1 
};

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void display(int digit){
	if(digit>=0 && digit <= 15){
		PORTC = pattern[digit];
		} else if(digit > 15){
		PORTC = pattern[14];
	}
	wait(200);
}

int main(void)
{
	DDRC = 0xFF;
	DDRD = 0x00;
    /* Replace with your application code */
	int index = 0;
    while (1) 
    {
		if(PIND & 0b00000001){
			index++;
		} else if(PIND & 0b00000010){
			index--;
			if(index < 0){
				index = 0;
			}
		} else if(PIND & 0b00000100){
			index = 0;
		}
		display(index);
    }
}



