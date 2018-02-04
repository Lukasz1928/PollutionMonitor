#include <avr/io.h>
#include <avr/delay.h>

int main(void) {
	DDRC = 0xFF;
    while (1) {
		PORTC |= (1 << PC5);
		_delay_ms(1000);
		PORTC &= ~(1 << PC5);
		_delay_ms(1000);
    }
}

