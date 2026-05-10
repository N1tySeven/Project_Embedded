#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "lcd/lcd.h"
#include "keypad/keypad.h"
#include "utils/delay.h"
#include "spi/spi.h"
#include "sdcard/sdcard.h"
#include "rfid/mfrc522.h"
#include "fatfs/ff.h"
#include "fatfs/diskio.h"

FATFS fs;
FIL file;

void timer0_init()
{
    TCCR0A |= (1 << WGM01);

    TCCR0B |= (1 << CS01) |
              (1 << CS00);

    TIMSK0 |= (1 << OCIE0A);

    OCR0A = 124;
}

ISR(TIMER0_COMPA_vect)
{
    ms_counting++;
}

// เช็คว่ามี UID นี้อยู่ในไฟล์ uid.txt แล้วหรือยัง
uint8_t check_duplicate(const char* uid_str)
{
    char line[32];
    uint8_t is_duplicate = 0;

    if (f_open(&file, "uid.txt", FA_READ) == FR_OK)
    {
        while (f_gets(line, sizeof(line), &file))
        {
            line[strcspn(line, "\r\n")] = 0;

            if (strcmp(line, uid_str) == 0)
            {
                is_duplicate = 1;
                break;
            }
        }
        f_close(&file);
    }

    return is_duplicate;
}

// บันทึก UID ลงในไฟล์ uid.txt
// คืนค่า: 0 = สำเร็จ, อื่นๆ = Error
uint8_t save_uid(const char* uid_str, char* result_msg)
{
    FRESULT res;
    
    // ใช้ FA_OPEN_APPEND เพื่อเปิดไฟล์และเลื่อน pointer ไปท้ายไฟล์ให้อัตโนมัติ
    res = f_open(&file, "uid.txt", FA_WRITE | FA_OPEN_APPEND);
    if (res != FR_OK)
    {
        sprintf(result_msg, "Open:%d", res);
        return 1;
    }

    UINT bw;
    uint8_t len = strlen(uid_str);

    // เขียน UID
    res = f_write(&file, uid_str, len, &bw);
    if (res != FR_OK || bw != len)
    {
        sprintf(result_msg, "Write1:%d/%d", res, bw);
        f_close(&file);
        return 2;
    }

    // เขียน newline (\r\n สำหรับระบบไฟล์ FAT ทั่วไป)
    res = f_write(&file, "\r\n", 2, &bw);
    if (res != FR_OK || bw != 2)
    {
        sprintf(result_msg, "Write2:%d", res);
        f_close(&file);
        return 2;
    }

    // บังคับให้เขียนลง SD Card ทันที
    res = f_sync(&file);
    if (res != FR_OK)
    {
        sprintf(result_msg, "Sync:%d", res);
        f_close(&file);
        return 5;
    }

    // อ่านขนาดไฟล์ล่าสุดเพื่อดูว่ามันเพิ่มขึ้นจริงไหม
    DWORD current_size = f_size(&file);

    res = f_close(&file);
    if (res != FR_OK)
    {
        sprintf(result_msg, "Close:%d", res);
        return 3;
    }

    sprintf(result_msg, "S:%lu", current_size);
    return 0;
}

int main(void)
{
    timer0_init();
    sei();

    lcd_init();
    keypad_init();
    spi_init();

    // ตั้งค่า SD Card: CS = HIGH (ปิด), MISO อ่านจาก PC4
    sdcard_init();
    sdcard_deselect();
    sd_spi_init();

    // === Mount SD Card ครั้งแรกครั้งเดียวตอนเปิดเครื่อง ===
    lcd_command(0x01);
    lcd_print("Init SD Card...");
    sd_spi_begin();
    FRESULT res = f_mount(&fs, "", 1);
    sdcard_deselect();
    sd_spi_end();

    if (res != FR_OK)
    {
        lcd_command(0xC0);
        char err[16];
        sprintf(err, "SD Err: %d", res);
        lcd_print(err);
        delay_ms(3000);
    }

    // เริ่มต้น RFID (Hardware SPI 500kHz, SD Card ไม่กวน)
    mfrc522_init();

    uint8_t status;
    uint8_t str[MAX_LEN];
    char uid_str[16];

    while(1)
    {
        lcd_command(0x01);
        lcd_print("Ready to scan");

        // === ขั้นตอนที่ 1: วนรอสแกนบัตร RFID ===
        while(1)
        {
            status = mfrc522_request(PICC_REQIDL, str);
            if (status == 0)
            {
                status = mfrc522_anticoll(str);
                if (status == 0)
                {
                    break;
                }
            }
            delay_ms(100);
        }

        // แปลง UID เป็น String
        sprintf(uid_str, "%02X%02X%02X%02X%02X",
                str[0], str[1], str[2], str[3], str[4]);

        // แสดง UID บน LCD
        lcd_command(0x01);
        lcd_print("UID:");
        lcd_command(0xC0);
        lcd_print(uid_str);
        delay_ms(1000);

        // === ขั้นตอนที่ 2: ถามว่าจะบันทึกไหม ===
        lcd_command(0x01);
        lcd_print(uid_str);
        lcd_command(0xC0);
        lcd_print("# Save  * Cancel");

        // รอกด Keypad
        char key = 0;
        while(key == 0)
        {
            key = keypad_getkey();
            delay_ms(50);
        }

        if (key == '#')
        {
            // === ขั้นตอนที่ 3: เปิด SD Card (Bit-Bang SPI), บันทึก, ปิด ===
            lcd_command(0x01);
            lcd_print("Saving...");

            // สลับเป็น Bit-Bang SPI สำหรับ SD Card
            sd_spi_begin();

            lcd_command(0xC0);

            if (check_duplicate(uid_str))
            {
                lcd_print("Duplicate!");
            }
            else
            {
                char status_msg[16];
                save_uid(uid_str, status_msg);
                lcd_print(status_msg);
            }

            // ปลด SD Card ออกจาก SPI Bus
            sdcard_deselect();

            // สลับกลับเป็น Hardware SPI สำหรับ RFID
            sd_spi_end();

            // init RFID ใหม่
            mfrc522_init();

            delay_ms(2000);
        }
        else
        {
            lcd_command(0x01);
            lcd_print("Cancelled");
            delay_ms(1000);
        }
    }
}
