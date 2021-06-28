/*
 * Ultrasonic sensor HC-05 interfacing with AVR ATmega16
 * http://www.electronicwings.com
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#define SPEAKER_PORT PORTC
#define SPEAKER_DDR DDRC
#define SPEAKER_PIN 7

void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void PLAYNOTE(float duration, float frequency);
int main(void)
{
	while(1){
	PLAYNOTE(500,250);
	wait(200);
	}
}

void PLAYNOTE(float duration, float frequency){
	long int i, cycles;
	float half_period;
	float wavelength;
	
	wavelength=(1/frequency)*1000;
	
	cycles = duration/wavelength;
	
	half_period = wavelength/2;
	
	SPEAKER_DDR |= (1 << SPEAKER_PIN);
	
	for(i=0;i<cycles;i++){
		wait(half_period);
		
		SPEAKER_PORT |= (1<<SPEAKER_PIN);
		
		wait(half_period);
		
		SPEAKER_PORT &= ~(1<<SPEAKER_PIN);
	}
	return;
}