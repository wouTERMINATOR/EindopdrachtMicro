/*
 * B3.c
 *
 * Created: 24-2-2021 14:45:58
 * Author : woute
 */ 

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define F_CPU 8e6

volatile int TimerPreset = -10;
volatile int tenthValue = 0;

void wait( int ms) {
	for(int i = 0; i < ms ; i++){
		_delay_ms(1);
	}
}

ISR(TIMER2_OVF_vect){
	TCNT2 = TimerPreset;
	tenthValue++;
}
void timer2Init(void){
	TCNT2 = TimerPreset;
	TIMSK |= 0b01000000;
	sei();
	TCCR2 = 0x07;
}

int main(void)
{
	DDRD &= 0b10000000;
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	timer2Init();
	
    while (1) 
    {
		PORTA = TCNT2;
		PORTB = tenthValue;
		wait(10);
	}
}

