#include <avr/io.h>
#include <avr/delay.h>
#include "display.h"

int main(void) {
	display_init();
	display_write_multiline("line1 abc", "line2 xyz");
	while(1) {
		
	}
}

