# Module: Keypad

โมดูลสำหรับจัดการ Input จาก Matrix Keypad ขนาด 4x4

## Pin Connection (ATmega328P)

| Keypad Pin | MCU Pin | Function |
|------------|---------|----------|
| Row 1      | PD7     | Output   |
| Row 2      | PD6     | Output   |
| Row 3      | PD5     | Output   |
| Row 4      | PD4     | Output   |
| Col 1      | PD0     | Input    |
| Col 2      | PD1     | Input    |
| Col 3      | PD2     | Input    |
| Col 4      | PB0     | Input    |

## API Reference

### `void keypad_init(void)`
ตั้งค่าทิศทางของขา (DDR) สำหรับ Rows (Output) และ Columns (Input) พร้อมเปิดใช้งาน Pull-up

### `char keypad_getkey(void)`
สแกนหาปุ่มที่ถูกกด หากมีการกดปุ่มจะคืนค่าเป็นตัวอักษรของปุ่มนั้น ('1'-'D', '*', '#') หากไม่มีการกดจะคืนค่าเป็น 0

## ตัวอย่างการใช้งาน
```c
keypad_init();
char key = keypad_getkey();
if (key != 0) {
    // ทำบางอย่างเมื่อกดปุ่ม
}
```
