/*
 * LCD_Source.c
 *
 *
 *  Author: Ahmed_Ashraf
 */ 
/************************************************************************/
/* please note that there's a lot of commands we can perform on our LCD,
	0x30	 => To display content in one line in 5*7 matrix
	0x38	 => two lines
	0x20	 => 4 bit data in one line
	0x28	 => 4 bit data in two lines
	0x06	 => entry mode
	0x08	 => clear without clearing RAM
	0x0E	 => (cursor & display) = on
	0x0C	 => (cursor & display) = off
	0x0F	 => cursor blinking
	0x18	 => shift complete displaying data to the left
	0x1C	 => shift complete displaying data to the right
	0x10	 => move cursor to the left
	0x14	 => move it to the right
	0x01	 => clear
	0x80+add => Set DDRAM address on cursor position
	                                                                     */
/************************************************************************/
#include "LCD.h"


// DATA_PORT	
// DATA_DDR	
//
// CTRL_PORT	
// CTRL_DDR	
//
// RS_PIN		4
// RW_PIN		5
// ENABLE_PIN	6

void send_cmd(unsigned char cmd){
	DATA_PORT = cmd;
	CTRL_PORT &= ~(1<<RS_PIN);
	CTRL_PORT &= ~(1<<RW_PIN);
	CTRL_PORT |= (1<<ENABLE_PIN);
	_delay_ms(1);
	CTRL_PORT &= ~(1<<RS_PIN)|~(1<<RW_PIN)|~(1<<ENABLE_PIN);
	_delay_ms(20);
	return;
}

void lcd_init(void){
	// initialization
	CTRL_DDR = 0xFF;
	CTRL_PORT = 0x00;
	DATA_DDR = 0xFF;
	DATA_PORT = 0x00;
	// clear, 8bit mode, cursor on
	send_cmd(0x01);
	_delay_ms(1);
	send_cmd(0x38);
	_delay_ms(1);
	send_cmd(0x0E);
	_delay_ms(1);
	send_cmd(0x06);
	_delay_ms(1);
}

void lcd_Clear(void){
	send_cmd(0x01);
	_delay_ms(20);
}

void lcd_show_data(char *Data_String){
	while (*Data_String > 0){
		send_data(*Data_String++);
	}
}

void send_data(unsigned char data){
	DATA_PORT = data;
	CTRL_PORT &= ~(1<<RW_PIN);
	CTRL_PORT |= (1<<RS_PIN);
	CTRL_PORT |= (1<<ENABLE_PIN);
	_delay_ms(1);
	CTRL_PORT &= ~(1<<RW_PIN);
	CTRL_PORT &= ~(1<<ENABLE_PIN);
	CTRL_PORT |= (1<<RS_PIN);
	_delay_ms(20);
}

void lcd_goto(unsigned char y, unsigned char x)
{
	unsigned char firstAddress[] = {0x80,0xC0,0x94,0xD4};
	send_cmd(firstAddress[y-1] + x-1);
	_delay_ms(10);
}