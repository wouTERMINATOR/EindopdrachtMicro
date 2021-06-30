/*
 * B4.c
 *
 * Created: 10-2-2021 15:07:24
 * Author : woute
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8e6

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 

PATTERN_STRUCT pattern[] = { 
	{0x3F, 300}, {0x30, 300}, 
	{0x5B, 300}, {0x4F, 300}, 
	{0x66, 300}, {0x6D, 300}, 
	{0x7D, 300}, {0x07, 300}, 
	{0x7F, 300}, {0x6F, 300},
	{0xFF, 0}
};

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );	
	}
}

int main( void ) {
	DDRD = 0b11111111;				
	
	while (1) {
		int index = 0;
		while( pattern[index].delay != 0 ) {
			PORTD = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
	}
	return 1;
}