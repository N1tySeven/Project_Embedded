# Module: RFID (MFRC522)

โมดูลสำหรับอ่านบัตร RFID โดยใช้ชิป MFRC522 ผ่านโปรโตคอล Hardware SPI

## Pin Connection (ATmega328P)

| MFRC522 Pin | MCU Pin | Function |
|-------------|---------|----------|
| SDA (SS)    | PB2     | SPI Slave Select |
| SCK         | PB5     | SPI Clock |
| MOSI        | PB3     | SPI Master Out |
| MISO        | PB4     | SPI Master In |
| RST         | PC5     | Reset |

## API Reference

### `void mfrc522_init(void)`
เริ่มต้นการทำงานของ MFRC522 และตั้งค่าสายสัญญาณ SPI

### `uint8_t mfrc522_request(uint8_t reqMode, uint8_t *TagType)`
ค้นหาการ์ด RFID ในระยะ

### `uint8_t mfrc522_anticoll(uint8_t *serNum)`
อ่านหมายเลข ID (UID) ของการ์ดที่พบ

### `uint8_t mfrc522_get_version(void)`
อ่านเวอร์ชันของชิป MFRC522

## ตัวอย่างการใช้งาน
```c
mfrc522_init();
uint8_t status, str[16];
status = mfrc522_request(PICC_REQIDL, str);
if (status == 0) {
    status = mfrc522_anticoll(str);
    // หมายเลข ID จะอยู่ใน str[0] ถึง str[3]
}
```
