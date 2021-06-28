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
	int delayTimer = 1000;
	int boolean = 1;
	int STATE = 0;
	int isOn = 1;
    /* Replace with your application code */
    while (1) 
    {
		if(PINC == 0b00000001){
			if(boolean == 1){
				if(STATE == 1){
					STATE = 0;
					delayTimer = 1000;
				} else {
					STATE = 1;
					delayTimer = 250;
				}
				boolean = 0;
			}	
		} else {
			boolean = 1;	
		}
		if(isOn == 1){
			PORTD = 0B00000000;
			wait(delayTimer);
			isOn = 0;
		}else {
			PORTD = 0B10000000;
			wait(delayTimer);
			isOn = 1;
		}
		
		
    }
}

