# Module: SD Card

โมดูลสำหรับจัดการ SD Card โดยใช้เทคนิค Bit-bang SPI เพื่อเลี่ยงปัญหาการขัดแย้งของสายสัญญาณ (Bus Contention) กับโมดูล RFID

## Pin Connection (ATmega328P)

| SD Module Pin | MCU Pin | Function |
|---------------|---------|----------|
| CS            | PD3     | Chip Select |
| SCK           | PB5     | Serial Clock (Shared) |
| MOSI          | PB3     | Master Out (Shared) |
| MISO          | PC4     | Master In (Unique) |

*ความสำคัญ: ใช้ขา MISO ที่ PC4 แทน PB4 เพื่อไม่ให้ชนกับ RFID*

## API Reference

### `void sdcard_init(void)`
ตั้งค่าขา CS ของ SD Card

### `void sd_spi_init(void)`
ตั้งค่าขา PC4 เป็น Input สำหรับ Bit-bang SPI

### `void sd_spi_begin(void)`
ปิด Hardware SPI และตั้งค่าขา MOSI/SCK เป็นโหมดควบคุมด้วย Manual (Bit-bang)

### `void sd_spi_end(void)`
คืนค่าการควบคุมขาสัญญาณกลับไปให้ Hardware SPI (สำหรับใช้งาน RFID ต่อ)

### `uint8_t sd_spi_transfer(uint8_t data)`
ส่งและรับข้อมูลผ่าน Bit-bang SPI ความเร็วประมาณ 167kHz

## การใช้งานร่วมกับ FatFs
โมดูลนี้ถูกออกแบบมาเพื่อใช้เป็น Low-level driver ใน `diskio.c` ของ FatFs โดยต้องเรียก `sd_spi_begin()` ก่อนทำการติดต่อกับ SD Card และ `sd_spi_end()` เมื่อเสร็จสิ้น
