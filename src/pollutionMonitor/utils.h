#ifndef UTILS_H
#define UTILS_H

#define SET(REG, BIT) (REG |= (1 << BIT))
#define UNSET(REG, BIT) (REG &= ~(1 << BIT))

void SPI_master_init(void);
void SPI_slave_init(void);
char SPI_write(unsigned char);
unsigned char SPI_read(void);

#endif