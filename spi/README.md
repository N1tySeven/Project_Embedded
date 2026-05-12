# Module: SPI

โมดูลสำหรับจัดการ Hardware SPI ของ ATmega328P

## ข้อมูลทางเทคนิค
- **Clock Speed:** 500kHz (F_CPU/16) สำหรับ RFID และ 125kHz (F_CPU/64) ในโหมด Slow
- **SPI Mode:** Mode 0 (CPOL=0, CPHA=0)

## API Reference

### `void spi_init(void)`
เริ่มต้น Hardware SPI Master mode

### `uint8_t spi_transfer(uint8_t data)`
ส่งข้อมูล 1 ไบต์และรับข้อมูลกลับมา 1 ไบต์แบบ Synchronous

### `void spi_slow(void)`
ลดความเร็วลงเหลือ 125kHz (สำหรับขั้นตอน Initialization ของ SD Card)

### `void spi_fast(void)`
เพิ่มความเร็วกลับเป็น 500kHz
