# Module: FatFs

ไลบรารีระบบจัดการไฟล์ (File System) สำหรับ Fat12/16/32 โดย Elm-ChaN

## โครงสร้างไฟล์
- `ff.c / ff.h`: ตัวหลักของไลบรารี
- `ffconf.h`: ไฟล์สำหรับปรับแต่งความสามารถ (Configurations)
- `diskio.c / diskio.h`: ส่วนเชื่อมต่อกับ Hardware (Low-level driver)

## การปรับแต่งในโปรเจกต์นี้
- เชื่อมต่อกับ SD Card ผ่านฟังก์ชันในโมดูล `sdcard/`
- ใช้ Bit-bang SPI เพื่อลดปัญหาการกวนกันของสัญญาณบน Bus
- รองรับการเปิดไฟล์ `uid.txt` เพื่ออ่านและบันทึกข้อมูลบัตร RFID และรหัส PIN
