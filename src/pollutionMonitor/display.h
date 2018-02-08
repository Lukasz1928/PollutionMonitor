#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_RS_DDR      DDRC
#define DISPLAY_RS_PORT     PORTC
#define DISPLAY_RS          PC5

#define DISPLAY_E_DDR       DDRC
#define DISPLAY_E_PORT      PORTC
#define DISPLAY_E           PC3

#define DISPLAY_DB4_DDR     DDRD
#define DISPLAY_DB4_PORT    PORTD
#define DISPLAY_DB4	        PD4

#define DISPLAY_DB5_DDR     DDRD
#define DISPLAY_DB5_PORT    PORTD
#define DISPLAY_DB5	        PD5

#define DISPLAY_DB6_DDR     DDRD
#define DISPLAY_DB6_PORT    PORTD
#define DISPLAY_DB6	        PD6

#define DISPLAY_DB7_DDR     DDRD
#define DISPLAY_DB7_PORT    PORTD
#define DISPLAY_DB7         PD7


#define DISPLAY_CLEAR               0b1

#define DISPLAY_HOME_RETURN         0b10

#define DISPLAY_ENTRY_MODE          0b100
#define HD44780_EM_SHIFT_CURSOR		0
#define HD44780_EM_INCREMENT		0b10

#define DISPLAY_TOGGLE		        0b1000
#define DISPLAY_TOGGLE_OFF			0
#define DISPLAY_TOGGLE_ON			0b100

#define DISPLAY_FUNCTION_SET        0b100000
#define DISPLAY_FONT5x7	            0
#define DISPLAY_LINES_TWO           0b1000
#define DISPLAY_4_BIT               0

#define HD44780_DDRAM_SET           0b10000000

void display_write_command(unsigned char);
void display_write_data(unsigned char);
void display_write_text(char*);
void display_write_multiline(char*, char*);
void display_set_cursor(unsigned char, unsigned char);
void display_clear(void);
void display_reset_cursor(void);
void display_init(void);

#endif
