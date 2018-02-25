#ifndef SPI_H
#define SPI_H
#include <stdint.h>

void SPI_master_init(void);
void SPI_slave_init(void);
uint8_t SPI_write(uint8_t);

#endif