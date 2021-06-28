/*
 * eindopdracht.c
 *
 * Created: 17-3-2021 14:02:18
 * Author : woute
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

	int counter_in_ms = 0;
	int temp = 1;
	
void PLAYNOTE(float duration, float frequency);

void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT1_vect ) {
	PLAYNOTE(100, 100);
	temp = 0;
}
ISR( INT0_vect ) {
	PLAYNOTE(100, 100);
	temp = 0;
}


int main(void)
{
	DDRD = 0b01100100; // used for sensor pin 0 is for trigger pin 1 is for echo

	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x02;			// Enable INT1 & INT0
	
	sei();
	
	PLAYNOTE(200, 250);
	while(1){
		check_ultrasonic();
	    PLAYNOTE(500,counter_in_ms);
    }
	return 1;
}

void check_ultrasonic(){
	temp = 1;
	counter_in_ms = 0;
	PORTD = 0b00000100;
	_delay_us(10);
	PORTD = 0b00000100;
	while(1){
		counter_in_ms = counter_in_ms + 100;
		if(temp == 0){
			break;
		}
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



