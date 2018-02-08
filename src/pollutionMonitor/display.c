#include "display.h"
#include "utils.h"
#include <avr/io.h>
#include <util/delay.h>

void display_write_halfbyte(unsigned char halfbyte) {
	(halfbyte & 1) ? SET(DISPLAY_DB4_PORT, DISPLAY_DB4) : UNSET(DISPLAY_DB4_PORT, DISPLAY_DB4);
	(halfbyte & 2) ? SET(DISPLAY_DB5_PORT, DISPLAY_DB5) : UNSET(DISPLAY_DB5_PORT, DISPLAY_DB5);
	(halfbyte & 4) ? SET(DISPLAY_DB6_PORT, DISPLAY_DB6) : UNSET(DISPLAY_DB6_PORT, DISPLAY_DB6);
	(halfbyte & 8) ? SET(DISPLAY_DB7_PORT, DISPLAY_DB7) : UNSET(DISPLAY_DB7_PORT, DISPLAY_DB7);
}

void display_write_byte(unsigned char byte) {
	SET(DISPLAY_E_PORT, DISPLAY_E);
	display_write_halfbyte(byte >> 4);
	UNSET(DISPLAY_E_PORT, DISPLAY_E);
	_delay_us(50);
	SET(DISPLAY_E_PORT, DISPLAY_E);
	display_write_halfbyte(byte);
	UNSET(DISPLAY_E_PORT, DISPLAY_E);
	_delay_us(50);
}

void display_write_command(unsigned char command){
	UNSET(DISPLAY_RS_PORT, DISPLAY_RS);
	display_write_byte(command);
}

void display_write_data(unsigned char dataToWrite) {
	SET(DISPLAY_RS_PORT, DISPLAY_RS);
	display_write_byte(dataToWrite);
}

void display_write_text(char* text) {
	while(*text) {
		display_write_data(*text++);
	}
}

void display_write_multiline(char* text1, char* text2) {
	display_write_text(text1);
	display_set_cursor(0, 1);
	display_write_text(text2);
}


void display_set_cursor(unsigned char x, unsigned char y) {
	display_write_command(HD44780_DDRAM_SET | (x + (0x40 * y)));
}

void display_clear(void) {
	display_write_command(DISPLAY_CLEAR);
	_delay_ms(2);
}

void display_reset_cursor(void) {
	display_write_command(DISPLAY_HOME_RETURN);
	_delay_ms(2);
}
void display_init(void) {
	SET(DISPLAY_DB4_DDR, DISPLAY_DB4);
	SET(DISPLAY_DB5_DDR, DISPLAY_DB5);
	SET(DISPLAY_DB6_DDR, DISPLAY_DB6);
	SET(DISPLAY_DB7_DDR, DISPLAY_DB7);
	SET(DISPLAY_E_DDR, DISPLAY_E);
	SET(DISPLAY_RS_DDR, DISPLAY_RS);
	
	_delay_ms(15);
	UNSET(DISPLAY_RS_PORT, DISPLAY_RS);
	for(char i = 0; i < 3; ++i) {
		SET(DISPLAY_E_PORT, DISPLAY_E);
		display_write_halfbyte(0x03);
		UNSET(DISPLAY_E_PORT, DISPLAY_E);
		_delay_ms(5);
	}
	SET(DISPLAY_E_PORT, DISPLAY_E);
	display_write_halfbyte(0x02);
	UNSET(DISPLAY_E_PORT, DISPLAY_E);
	_delay_ms(1);
	display_write_command(DISPLAY_FUNCTION_SET | DISPLAY_4_BIT);
	display_write_command(DISPLAY_FUNCTION_SET | DISPLAY_LINES_TWO | DISPLAY_FONT5x7);
	display_write_command(DISPLAY_TOGGLE | DISPLAY_TOGGLE_OFF);
	display_write_command(DISPLAY_CLEAR);
	_delay_ms(2);
	display_write_command(DISPLAY_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);
	display_write_command(DISPLAY_TOGGLE | DISPLAY_TOGGLE_ON);
}

