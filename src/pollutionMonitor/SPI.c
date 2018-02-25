#include "SPI.h"
#include "wireless.h"
#include "utils.h"
#include <avr/io.h>
#include <avr/delay.h>

void SPI_master_init(void) {
	DDRB = (1 << DDB3) | (1 << DDB5) | (1 << DDB2);
	//SPI frequency = 0.25 * fosc
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << DORD);
}

void SPI_slave_init(void) {
	DDRB = (1 << DDB4);
	SPCR = (1 << SPE);
}

uint8_t SPI_write(uint8_t data) {
	SPDR = data;
	//wait for transmission to finish
	while(!(SPSR &  (1 << SPIF)));
	return SPDR;
}
