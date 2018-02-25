#include <avr/io.h>
#include <avr/delay.h>
#include "display.h"
#include "wireless.h"
#include "SPI.h"
#include <stdio.h>

int main(void) {
	display_init();
	SPI_master_init();
	wireless_init();
	display_write_multiline(a, "");
	while(1) {
		
	}
}

