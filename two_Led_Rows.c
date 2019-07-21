#include <avr/io.h>
#include <util/delay.h>

// a great notation is when you inter a number like (0->7) sometimes it represents a pin

int main(void) //main starts
{
	// here I will use multiple Leds to light one after another (Fastlly) for the first row, the second row will be slower
	DDRB |= 0x1F;
	DDRD |= 0x1F;
	int LED[2] = {0,0};						// it's an array which holds the pin which should be turned,(2 as I have 2 rows) 
	TCCR1B |= (0<<CS10) | (1<<CS11) | (0<<CS12);
	PORTB = 0;
	PORTD = 0;
	while(1){
	if (TCNT1 > 15000){
		TCNT1 = 0;
		PORTB = 1<<LED[0];
		LED[0]++;
		if (LED[0] > 4){
			LED[0] = 0;
			PORTD = 1<<LED[1];
			LED[1]++;
			if (LED[1] > 4) LED[1] = 0;
		}
	}
	}	
} //main end
