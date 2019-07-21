#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
// a great notation is when you inter a number like (0->7) sometimes it represents a pin

int main(void) //main starts
{
	// here I will use multiple Leds to light one after another (Fastlly) for the first row, the second row will be slower
	DDRB |= (1<<PB0);
	TCCR1B |= (0<<CS10) | (1<<CS11) | (0<<CS12) | (1<<WGM12);
	OCR1A = 15000;
	PORTB = 0;
	TIMSK |= (1<<OCIE1A);
	sei();
	while(1){
	}
} //main end

ISR (TIMER1_COMPA_vect){
	PORTB ^= (1<<PB0);
}



