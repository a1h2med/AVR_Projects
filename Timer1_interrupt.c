#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) //main starts
{
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



