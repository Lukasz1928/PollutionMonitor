#include "utils.h"

void SPI_master_init(void) {
	DDRB = (1 << DDB3) | (1 << DDB5);
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_slave_init(void) {
	DDRB = (1 << DDB4);
	SPCR = (1 << SPE);
}

char SPI_write(unsigned char data) {
	SPDR = data;
	while(!(SPSR &  (1 << SPIF)));
	return SPDR;
}

unsigned char SPI_read(void) {
	_delay_us(10);
	UNSET(WIRELESS_CSN_PORT, WIRELESS_CSN);
	_delay_us(10);
	SPI_write();
}