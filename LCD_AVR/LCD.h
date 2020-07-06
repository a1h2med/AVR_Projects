/*
 * LCD.h
 *
 * 
 *  Author: Ahmed_Ashraf
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL

#define DATA_PORT	PORTD
#define DATA_DDR	DDRD

#define CTRL_PORT	PORTA
#define CTRL_DDR	DDRA

#define RS_PIN		4
#define RW_PIN		5
#define ENABLE_PIN	6

void send_cmd(unsigned char cmd);
void send_data(unsigned char data);
void lcd_init(void);
void lcd_show_data(char *Data_String);
void lcd_Clear(void);
void lcd_goto(unsigned char y, unsigned char x);


#endif /* LCD_H_ */