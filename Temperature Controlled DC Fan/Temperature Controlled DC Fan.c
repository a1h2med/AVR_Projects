#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(){
	DDRB |= (1<<PB0);															// initializing PortB
	PORTB = 0;
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS2) | (1<<ADPS0) | (1<<ADIE);		// Initializing ADC,64 Prescaler as I set the frequency to 80 
	sei();
	ADMUX |= 0b00000;															// Using ADC0
	ADMUX |= (1<<REFS0) | (0<<REFS1) | (0<<ADLAR);								// Using AVCC with external cap. at AREF Pin
	ADCSRA |= (1<<ADSC);														// starting conversion
	while(1){
	}
}

ISR (ADC_vect){																	// Interrupt Service Function
	
	// getting the 10-bit reading from the ADC
	uint8_t low = ADCL;															
	uint16_t reading = (ADCH<<8) | low;											
	
	// converting the reading into degree celsius
	float celesius = (reading*4.88)/10;
	
	// checking on the degree whether it's above the required or not,if yes then Turn the Fan on , else turn it off
	if (celesius > 60)
		PORTB = (1<<PB0);
	else 
		PORTB = (0<<PB0);
	
	ADCSRA |= (1<<ADSC);														// Take another reading
}

