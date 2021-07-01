
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC:
void adcInit( void )
{
	ADMUX = 0b11100001;			// AREF=2,56 V, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no free running, division by 64
}


// Main program: Counting on T1
int main( void )
{
	DDRF = 0x00;					// set PORTF for input (ADC)
	DDRA = 0xFF;					// set PORTA for output
	DDRB = 0x00;					// set PORTB for intput
	adcInit();						// initialize ADC
	int bool = 0;

	while (1)
	{
		ADCSRA |= BIT(6);				// Start ADC
		if(PORTB == 0b10000000){
			bool = 1;
		}
		while ( bool == 1 ) ;		// Wait for completion
		PORTA = ADCH;					// Show MSB (bit 9:2) of ADC
		wait(500);						// every 50 ms (busy waiting)
	}
}
