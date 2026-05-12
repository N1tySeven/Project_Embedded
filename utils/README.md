# Module: Utils

รวมฟังก์ชันเสริมสำหรับโปรเจกต์ (Servo และ Delay)

## 1. Servo Control (`servo.h`)
ควบคุม Continuous Rotation Servo โดยใช้ Timer 1 (Fast PWM)

### Pin Connection
- **MCU Pin:** PB1 (OC1A)

### API
- `servo_init()`: ตั้งค่า Timer 1 และขา Output
- `servo_lock()`: หมุนไปในทิศทางล็อคประตู
- `servo_unlock()`: หมุนไปในทิศทางปลดล็อคประตู
- `servo_stop()`: หยุดการหมุนของมอเตอร์

## 2. Delay (`delay.h`)
ฟังก์ชันสำหรับหน่วงเวลาโดยอ้างอิงจาก Timer 0

### API
- `delay_ms(uint16_t ms)`: หน่วงเวลาหน่วยมิลลิวินาที
