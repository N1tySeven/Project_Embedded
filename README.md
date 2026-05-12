# AVR RFID Access Control System with SD Card Logging

โปรเจกต์ระบบควบคุมการเข้าออก (Access Control) ด้วยบัตร RFID พร้อมระบบบันทึกข้อมูลลง SD Card และหน้าจอแสดงผล LCD พัฒนาด้วยภาษา C สำหรับไมโครคอนโทรลเลอร์ AVR (ATmega328P) โดยไม่ใช้ Arduino Framework (Bare-metal C)

## 🌟 ฟีเจอร์หลัก (Features)
- **RFID MFRC522:** สแกนบัตร RFID/NFC เพื่ออ่านค่า UID
- **SD Card (FAT32):** บันทึกหรืออ่านข้อมูลผ่านระบบไฟล์ FatFs โดยใช้เทคนิค Bit-bang SPI บางส่วนเพื่อแก้ปัญหาสัญญาณชนกัน (SPI Bus Contention) กับโมดูล RFID
- **16x2 / 20x4 LCD:** แสดงผลสถานะระบบและ UID ของบัตร (เชื่อมต่อแบบ 4-bit)
- **4x4 Matrix Keypad:** รองรับการป้อนรหัสผ่านหรือคำสั่งเพิ่มเติม
- **Continuous Rotation Servo:** ควบคุมการเปิด/ปิดประตูด้วย PWM (สามารถจูนความเร็วและเวลาได้อิสระ)

## 🛠️ ฮาร์ดแวร์ที่ใช้ (Hardware Requirements)
- ไมโครคอนโทรลเลอร์ AVR: **ATmega328P** (รันที่ 8MHz Internal Clock หรือ External)
- เครื่องอ่านบัตร: **MFRC522 RFID Module**
- ตัวอ่านการ์ด: **MicroSD Card Module** (ฟอร์แมตเป็น FAT32)
- หน้าจอ: **LCD 16x2** หรือ **20x4** (ไม่ต้องใช้โมดูล I2C)
- แป้นกด: **4x4 Matrix Keypad**
- มอเตอร์: **Continuous Rotation Servo Motor** (เช่น MG995/SG90 แบบหมุนรอบตัว)

## 📌 การต่อสาย (Pin Mapping)

### 1. จอ LCD (4-bit Mode)
- **RS:** `PB6`
- **EN:** `PB7`
- **D4-D7:** `PC0` - `PC3`

### 2. Matrix Keypad (4x4)
- **Rows 1-4:** `PD7`, `PD6`, `PD5`, `PD4`
- **Cols 1-4:** `PD0`, `PD1`, `PD2`, `PB0`

### 3. RFID MFRC522 (Hardware SPI)
- **SDA (CS):** `PB2`
- **SCK:** `PB5` *(แชร์กับ SD Card)*
- **MOSI:** `PB3` *(แชร์กับ SD Card)*
- **MISO:** `PB4`
- **RST:** `PC5`

### 4. SD Card Module (Bit-bang / Shared SPI)
- **CS:** `PD3`
- **SCK:** `PB5` *(แชร์กับ RFID)*
- **MOSI:** `PB3` *(แชร์กับ RFID)*
- **MISO:** `PC4` *(แยก MISO ออกมาอ่านแบบ Bit-bang เพื่อเลี่ยงปัญหาสัญญาณกวนกันบนบัส)*

### 5. Servo Motor
- **Signal (PWM):** `PB1` (Timer 1 - OC1A)

## ⚙️ โครงสร้างซอร์สโค้ด (Project Structure)
- `main.c` : เมนลูป ควบคุม State machine ของระบบ
- `rfid/` : ไลบรารีควบคุม MFRC522 (อ่านค่า Register, Anti-collision)
- `sdcard/` : ไลบรารีจัดการ SD Card และ Bit-bang SPI
- `fatfs/` : ไลบรารีจัดการระบบไฟล์ FAT32 ของคุณ ChaN (ปิดฟังก์ชันที่ไม่จำเป็นเพื่อประหยัด RAM/Flash)
- `lcd/` : ไลบรารีควบคุมหน้าจอ LCD แบบ 4-bit
- `keypad/` : ไลบรารีสแกนปุ่มกด Matrix Keypad
- `spi/` : ไลบรารี Hardware SPI 
- `utils/` : ฟังก์ชันหน่วงเวลา (Delay) และควบคุม Servo ด้วย PWM Timer 1

## 🔧 การตั้งค่า Servo (Servo Configuration)
สามารถปรับแต่งการหมุนของ Servo เพื่อเปิด/ปิดประตูได้ที่ไฟล์ `utils/servo.h`
```c
// ปรับความเร็ว (ยิ่งน้อยยิ่งช้า, เต็มสปีดที่ 500)
#define SERVO_SPEED_OFFSET 500

// ระยะเวลาที่ใช้ในการหมุน (มิลลิวินาที)
#define SERVO_ROTATION_TIME_MS  400
```

## ⚠️ ข้อควรระวัง (Notes)
- SD Card ต้องฟอร์แมตเป็น **FAT16** หรือ **FAT32** เท่านั้น (ปิดการใช้งาน exFAT ใน `ffconf.h` ไว้เพื่อป้องกัน RAM/Flash เต็มบนชิป ATmega328P)
- MISO ของ SD Card ถูกย้ายไปอ่านแบบซอฟต์แวร์ที่ขา `PC4` เนื่องจากโมดูล SD Card บางรุ่นไม่ยอมคืนสาย MISO (Tri-state issue) ทำให้กวนการทำงานของ RFID

## 💻 การคอมไพล์และอัปโหลด (Compilation)
โปรเจกต์นี้เขียนและพัฒนาบน **MPLAB X IDE** (หรือใช้ Atmel Studio / `avr-gcc` + `make` ก็ได้) โดยกำหนดค่า `F_CPU` เป็น `8000000L` (8 MHz)
