// Density Based Traffic Signal System Project
// In this project I have Two routes, in each one there's (3) IR sensors each one is far from the other with a certain distance
// The idea here is to control the traffic based on the number of the cars in each route
// I Will get the density of the cars in each route from the IR sensors located in each route and depending on the reading, I will control the Traffic Light
// Project Working description:
// If we have a reading from the 3 IR in the same route we will have four cases:
// 1- If there were no other reading from any other route, we will turn on the Red LED for the cars to pass
// 2- If there were two readings from two IR's, Red LED will be turned on for 2min.
// 3- If there were three readings from the 3 IR, Red LED will be turned on for 1min. then switch to another one.
// 4- If there were only one reading, Red LED will be turned on for 3min.

// If we have a reading from 2 IR in the same route we will have four cases:
// 1- If there were no red light (3 readings) we will turn on the red light till there's another update.
// 2- If there were 3 Readings, we will turn it on after 2min., and we will turn it for 30 sec.
// 3- If there were one Reading, we will turn it on for 2min.
// 4- If there were two Reading2, we will turn it on for 1min

// If we have a reading from 1 IR in the same route we will have four cases:
// 1- there's no other reading, we will turn the red light
// 2- there's two readings only,we will turn it on after 2min. and for 30sec.
// 3- there's two readings and three readings, we will turn it on after 5min. (if we have three readings from the same route, we will decrease the time to 3 min.).
// 4- there's only three readings, we will turn it after 6 min.

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void Reading_Route1(int *x,int *y,int *z);
void Reading_Route2(int *x,int *y,int *z);
void Timer_init();

volatile int Timer_Overflow_Value, Counter;
int main(){
	DDRB |= 0x0F;								// the first half will be for the first route where PB0 (red), PB1 (green), PB2 (red), PB3 (green)  				
	PORTB = 0;
	DDRD &= ~0x3F;
	PORTD = 0;
	int x = 0, y = 0, z = 0, a = 0, b = 0, c = 0 ;
	Timer_Overflow_Value = 0;
	while(1){
		Reading_Route1(&x,&y,&z);
		Reading_Route2(&a,&b,&c);
		if (x && y && z){
			if (a && b && c){
				PORTB |= 0x01;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}
			else if (a && b && !c){
				PORTB |= 0x01;
				Counter = 60;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 15;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}
			else if (a && !b && !c){
				PORTB |= 0x01;
				Counter = 86;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 15;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}
			else if (!(a && b && c)){
				PORTB |= 0x01;
			}
		}
		else if (x && y && !z){
			if (a && b && c){
				PORTB |= 0x04;
				Counter = 60;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 15;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
			}
			else if (a && b && !c){
				PORTB |= 0x01;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}
			else if (a && !b && !c){
				PORTB |= 0x01;
				Counter = 60;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}
			else if (!(a && b && c)){
				PORTB |= 0x01;
			}			
		}
		else if (x && !y && !z){
			if (a && b && c){
				PORTB |= 0x04;
				Counter = 86;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 15;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
			}
			else if (a && b && !c){
				PORTB |= 0x04;
				Counter = 60;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x01;			
				PORTB |= 0x02;
				}

			else if (a && !b && !c){
				PORTB |= 0x01;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}
			else if (!(a && b && c)){
				PORTB |= 0x01;
			}
		}
		if (a && b && c){
			if (x && y && z){
				PORTB |= 0x04;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
			}
			else if (x && y && !z){
				PORTB |= 0x04;
				Counter = 60;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 15;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
			}
			else if (x && !y && !z){
				PORTB |= 0x04;
				Counter = 86;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 15;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
			}
			else if (!(x && y && z)){
				PORTB |= 0x04;
			}
		}
		else if (a && b && !c){
			if (x && y && z){
				PORTB |= 0x01;
				Counter = 60;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 15;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}
			else if (x && y && !z){
				PORTB |= 0x04;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
			}
			else if (x && !y && !z){
				PORTB |= 0x04;
				Counter = 60;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
			}
			else if (!(x && y && z)){
				PORTB |= 0x04;
			}
		}
		else if (a && !b && !c){
			if (x && y && z){
				PORTB |= 0x01;
				Counter = 86;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 15;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}
			else if (x && y && !z){
				PORTB |= 0x01;
				Counter = 60;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
				PORTB |= 0x04;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
			}

			else if (x && !y && !z){
				PORTB |= 0x04;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x04;
				PORTB |= 0x08;
				PORTB |= 0x01;
				Counter = 30;
				Timer_init();
				PORTB &= ~0x01;
				PORTB |= 0x02;
			}
			else if (!(x && y && z)){
				PORTB |= 0x04;
			}
		}		
	}
}

void Reading_Route1(int *x,int *y,int *z){
	if (PD0 & PD1 & PD2){
		x = 1;
		y = 1;
		z = 1;
		return;
	}
	else if ((PD0 & PD1) == 1 & (PD2 == 0)){
		x = 1;
		y = 1;
		z = 0;
		return;
	}
	else if ((PD2 & PD1) == 0 & (PD0 == 1)){
		x = 1;
		y = 0;
		z = 0;
		return;
	}
	else {
		x = 0;
		y = 0;
		z = 0;
		return;
	}
}

void Reading_Route2(int *x,int *y,int *z){
	if (PD3 & PD4 & PD5){
		x = 1;
		y = 1;
		z = 1;
		return;
	}
	else if ((PD3 & PD4) == 1 & (PD5 == 0)){
		x = 1;
		y = 1;
		z = 0;
		return;
	}
	else if ((PD4 & PD5) == 0 & (PD3 == 1)){
		x = 1;
		y = 0;
		z = 0;
		return;
	}
	else {
		x = 0;
		y = 0;
		z = 0;
		return;
	}	
}

void Timer_init(){
	TCCR1B |= (1<<CS10) || (1<<CS11) || (0<<CS12);
	TCNT1 = 0;
	TIMSK |= (1<<TOIE1);
	sei();
}

ISR (TIMER1_OVF_vect){
	Timer_Overflow_Value++;
	if (Timer_Overflow_Value >= Counter){
		Timer_Overflow_Value = 0;
		TCCR1B &= ~(1<<CS10);
		TCCR1B &= ~(1<<CS11);
		TCCR1B &= ~(0<<CS12);
		TIMSK  &= ~(1<<TOIE1);
	}
}