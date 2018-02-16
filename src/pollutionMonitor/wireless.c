#include "wireless.h"
#include "utils.h"

void wireless_master_init(void) {
	SPI_master_init();
}

void wireless_slave_init(void) {
	SPI_slave_init();
}
