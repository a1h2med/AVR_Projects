#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) //main starts
{
	ADMUX = 0b0000;
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (0<<ADPS0) | (0<<ADPS1) | (1<<ADPS2);
	ADMUX |= (1<<ADLAR);
	sei();
	ADCSRA |= (1<<ADSC);
	ADMUX |= (1<<REFS0);
	while(1){
	}
} //main end

ISR (ADC_vect){
	float x = ADCH;
	ADCSRA |= (1<<ADSC);
}



