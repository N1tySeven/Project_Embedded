#ifndef SDCARD_H
#define SDCARD_H

#include <avr/io.h>

void sdcard_init(void);

void sdcard_select(void);

void sdcard_deselect(void);

// Bit-bang SPI สำหรับ SD Card (MISO อ่านจาก PC4)
void sd_spi_init(void);
void sd_spi_begin(void);
void sd_spi_end(void);
uint8_t sd_spi_transfer(uint8_t data);

#endif