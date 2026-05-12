# Module: LCD

โมดูลสำหรับควบคุมหน้าจอ LCD 16x2 ในโหมด 4-bit

## Pin Connection (ATmega328P)

| LCD Pin | MCU Pin | Function |
|---------|---------|----------|
| RS      | PB6     | Register Select |
| EN      | PB7     | Enable |
| D4      | PC0     | Data Bit 4 |
| D5      | PC1     | Data Bit 5 |
| D6      | PC2     | Data Bit 6 |
| D7      | PC3     | Data Bit 7 |

*หมายเหตุ: ขา R/W ควรต่อลง Ground*

## API Reference

### `void lcd_init(void)`
เริ่มต้นการทำงานของ LCD ในโหมด 4-bit และตั้งค่า Cursor

### `void lcd_command(uint8_t cmd)`
ส่งคำสั่ง (Command) ไปยัง LCD (เช่น ล้างหน้าจอ, ย้าย Cursor)

### `void lcd_data(uint8_t data)`
ส่งข้อมูล (Data/Character) ไปแสดงผลบนหน้าจอ

### `void lcd_print(const char *str)`
แสดงผลข้อความ string บนหน้าจอ

## ตัวอย่างการใช้งาน
```c
lcd_init();
lcd_print("Hello World!");
lcd_command(0xC0); // ย้ายไปบรรทัดที่ 2
lcd_print("Ready...");
```
