#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void spi_init(void);
uint8_t spi_transfer(uint8_t data);
void spi_slow(void);
void spi_fast(void);

#endif