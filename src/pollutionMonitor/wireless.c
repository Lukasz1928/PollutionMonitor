#include "wireless.h"
#include "utils.h"
#include "SPI.h"
#include <stdio.h>
#include "display.h"
#include <avr/delay.h>

void wireless_init(void) {
	_delay_ms(100);
	uint8_t data[5];
	
	//enable auto-acknowledgement for PIPE0
	data[0] = 0x01;
	wireless_write(EN_AA, data, 1);
	
	//enable RX address for PIPE0
	data[0] = 0x01;
	wireless_write(EN_RXADDR, data, 1);

	//setup address width
	data[0] = 0x03;
	wireless_write(SETUP_AW, data, 1);
	//wait 4000us before retransmission, max 15 attempts
	data[0] = 0xFF;
	wireless_write(SETUP_RETR, data, 1);
	
	//set frequency(2464MHz)
	data[0] = 0x40;
	wireless_write(RF_CH, data, 1);
	
	//set TX output power(0db) and speed(2Mbps)
	data[0] = 0x07;
	wireless_write(RF_SETUP, data, 1);
	
	//set receiver address for PIPE0
	int i;
	for(i = 0; i < 5; i++) {
		data[i] = 0x7C;
	}
	wireless_write(RX_ADDR_P0, data, 5);
	
	//set transmitter address for PIPE0
	for(i = 0; i < 5; i++) {
		data[i] = 0x7C;
	}
	wireless_write(TX_ADDR , data, 5);
	
	//set bytes per transmission
	data[0] = 5;
	wireless_write(RX_PW_P0, data, 1);
	
	//enable CRC, power up, set as transmitter
	data[0] = 0x1E; //00011110
	wireless_write(CONFIG, data, 1);
	
	_delay_ms(100);
}

uint8_t wireless_read(uint8_t reg) {
	_delay_us(10);
	//CSN to 0- nRF listens for command
	UNSET(WIRELESS_CSN_PORT, WIRELESS_CSN);
	_delay_us(10);
	//write command and register number
	SPI_write(R_REGISTER | reg);
	_delay_us(10);
	//write anything to shift registers
	reg = SPI_write(NOP);
	_delay_us(10);
	//stop listening
	SET(WIRELESS_CSN_PORT, WIRELESS_CSN);
	return reg;
}

void wireless_write(uint8_t reg, uint8_t* data, uint8_t len) {
	_delay_us(10);
	//CSN to 0- nRF listens for command
	UNSET(WIRELESS_CSN_PORT, WIRELESS_CSN);
	_delay_us(10);
	//write command and register number
	SPI_write(W_REGISTER + reg);
	_delay_us(10);
	for(uint8_t i = 0; i < len; i++) {
		SPI_write(data[i]);
		_delay_us(10);
	}
	//stop listening
	SET(WIRELESS_CSN_PORT, WIRELESS_CSN);
}