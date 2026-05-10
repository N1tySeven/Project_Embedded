#include "spi.h"

void spi_init(void)
{
    // MOSI SCK SS output
    DDRB |= (1 << PB3);
    DDRB |= (1 << PB5);
    DDRB |= (1 << PB2);

    // !! Deselect RFID (PB2 = SS) ทันทีเพื่อไม่ให้กวนสาย SPI
    PORTB |= (1 << PB2);

    // MISO input
    DDRB &= ~(1 << PB4);

    // Enable SPI Master (F_CPU/16 = 500kHz สำหรับ RFID)
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

// ลดความเร็ว SPI เป็น 125kHz สำหรับ SD Card
void spi_slow(void)
{
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1);
}

// เพิ่มความเร็ว SPI กลับเป็น 500kHz สำหรับ RFID
void spi_fast(void)
{
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t spi_transfer(uint8_t data)
{
    SPDR = data;

    while(!(SPSR & (1 << SPIF)));

    return SPDR;
}