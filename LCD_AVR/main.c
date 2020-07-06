/*
 * LCD.c
 *
 * Author : Ahmed Ashraf
 */ 

#include <avr/io.h>
#include "LCD.h"

int main(void)
{
	lcd_Clear();
	lcd_init();
	lcd_goto(1,2);
	lcd_show_data("SHOWING DATA");
	lcd_goto(2,3);
	lcd_show_data("ON LCD");
}

