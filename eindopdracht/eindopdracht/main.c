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

int counter_in_ms = 0; //Counter that counts the amount of time it took for the signal to return.
char signalRecieved = 1; //Used as a Boolean to show that the ultrasonic sensor received a signal.
	
void PLAYNOTE(float duration, float frequency);

void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//This interrupt gets triggered when the ultrasonic sensor(echo) receives a signal.
ISR( INT1_vect ) {
	signalRecieved = 1;
}

//This method sends a signal from the ultrasonic sensor
void checkUltrasonic(){
	signalRecieved = 0;
	counter_in_ms = 0;
	PORTD = 0b00000100;			// Starts sending a signal
	_delay_us(10);				// Waits for 10 ms
	PORTD = 0b00000000;			// Stops sending a signal
	while(1){
		counter_in_ms = counter_in_ms + 1;
		if(signalRecieved == 1){
			break;
		}
	}
}

int main(void)
{
	DDRD = 0b01100100; // used for sensor pin 2 is for trigger pin 1 is for echo
	
	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge 
	EIMSK |= 0x02;			// Enable INT1 & INT0
	
	sei();					
	
	PLAYNOTE(1000, 250);		//Starting tone to show the program has started
	while(1){
		checkUltrasonic();
	    PLAYNOTE(500,counter_in_ms/4);	
    }
	return 1;
}

//This method controls the sound emitted by the piëzo-element, using a specified frequency and duration.
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



