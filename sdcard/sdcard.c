#include "sdcard.h"
#include <util/delay.h>

#define SD_CS_LOW()   PORTD &= ~(1 << PD3)
#define SD_CS_HIGH()  PORTD |=  (1 << PD3)

void sdcard_init(void)
{
    DDRD |= (1 << PD3);

    SD_CS_HIGH();
}

void sdcard_select(void)
{
    SD_CS_LOW();
}

void sdcard_deselect(void)
{
    SD_CS_HIGH();
}

// ============================================
// Bit-Bang SPI สำหรับ SD Card
// MISO อ่านจากขา PC4 (แยกจาก RFID ที่ใช้ PB4)
// MOSI ใช้ PB3, SCK ใช้ PB5 (ร่วมกับ RFID)
// ============================================

void sd_spi_init(void)
{
    // PC4 = SD Card MISO (Input, ไม่ใส่ Pull-up)
    DDRC &= ~(1 << PC4);
    PORTC &= ~(1 << PC4);
}

void sd_spi_begin(void)
{
    // ปิด Hardware SPI เพื่อให้เราควบคุมขา PB3/PB5 เอง
    SPCR &= ~(1 << SPE);

    // ตั้ง MOSI และ SCK เป็น Output
    DDRB |= (1 << PB3) | (1 << PB5);

    // SCK เริ่มต้นที่ LOW (SPI Mode 0)
    PORTB &= ~(1 << PB5);
}

void sd_spi_end(void)
{
    // เปิด Hardware SPI กลับมาสำหรับ RFID (500kHz)
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t sd_spi_transfer(uint8_t data)
{
    uint8_t received = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        // ตั้งค่า MOSI ก่อน rising edge
        if (data & 0x80)
            PORTB |= (1 << PB3);
        else
            PORTB &= ~(1 << PB3);

        data <<= 1;

        // รอ setup time (1μs → ความเร็วรวม ~167kHz อยู่ในช่วง 100-400kHz)
        _delay_us(1);

        // SCK ขึ้น HIGH (rising edge — จุดที่ master sample ข้อมูล)
        PORTB |= (1 << PB5);

        // รอให้สัญญาณเสถียรก่อนอ่าน
        _delay_us(1);

        // อ่าน MISO จาก PC4
        received <<= 1;
        if (PINC & (1 << PC4))
            received |= 1;

        // SCK ลง LOW (falling edge — SD Card เปลี่ยนข้อมูลบิตถัดไป)
        PORTB &= ~(1 << PB5);

        // รอ hold time
        _delay_us(1);
    }

    return received;
}