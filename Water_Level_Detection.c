#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	
	DDRD = 0x00;		// Probes are connected to PORTD so I've made it as an input
	DDRA &= ~(0x03);	// Last two probes are connected to (PA0 and PA1), Also the PA3
	DDRC = 0xFF;		// 7-segment
	unsigned char seg[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

	while(1) //infinite loop
	{
		if (PINA & (1<<PA1)){			// tank is Full
			PORTA |= 0x04;
			PORTD = seg[8];
		}
		
		else if (PINA & (1<<PA0)){		// we got reading from seventh probe, so the Alarm will start for 1 sec. then ends
			PORTA |= 0x04;
			_delay_ms(1000);
			PORTA &= ~(0x04);
			_delay_ms(500);
			PORTD = seg[7];
		}
		
		else if (PIND & (1<<PD6)){		// we got reading from sixth probe
			PORTD = seg[6];
		}
		
		else if (PIND & (1<<PD5)){		// we got reading from fifth probe
			PORTD = seg[5];
		}
		
		else if (PIND & (1<<PD4)){		// we got reading from fourth probe
			PORTD = seg[4];
		}
		
		else if (PIND & (1<<PD3)){		// we got reading from third probe
			PORTD = seg[3];
		}

		else if (PIND & (1<<PD2)){		// we got reading from second probe
			PORTD = seg[2];
		}
		
		else if (PIND & (1<<PD1)){		// we got reading from first probe
			PORTD = seg[1];
		}
		
		else {
			PORTD = seg[0];				// Tank is empty
		}
	}
}
