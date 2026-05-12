#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "lcd/lcd.h"
#include "keypad/keypad.h"
#include "utils/delay.h"
#include "utils/servo.h"
#include "spi/spi.h"
#include "sdcard/sdcard.h"
#include "rfid/mfrc522.h"
#include "fatfs/ff.h"
#include "fatfs/diskio.h"

#define ADMIN_PASSWORD "1234"

FATFS fs;
FIL file;

/* =========================================================
 * TIMER0
 * ========================================================= */

void timer0_init(void)
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

/* =========================================================
 * INPUT FROM KEYPAD
 * ========================================================= */

void input_from_keypad(char* buffer, uint8_t max_len, uint8_t masked)
{
    uint8_t i = 0;

    buffer[0] = '\0';

    while(i < max_len)
    {
        char key = keypad_getkey();

        if (key != 0)
        {
            if (key == '#')
            {
                while(keypad_getkey() != 0);
                break;
            }
            else if (key == '*')
            {
                while(keypad_getkey() != 0);

                i = 0;
                buffer[0] = '\0';

                lcd_command(0xC0);
                lcd_print("                ");

                lcd_command(0xC0);

                continue;
            }

            buffer[i] = key;
            buffer[i + 1] = '\0';

            if (masked)
            {
                lcd_print("*");
            }
            else
            {
                char tmp[2] = {key, '\0'};
                lcd_print(tmp);
            }

            i++;

            while(keypad_getkey() != 0);
        }

        delay_ms(10);
    }

    buffer[i] = '\0';
}

/* =========================================================
 * FIND UID & PIN
 * ========================================================= */

uint8_t find_uid_and_pin(const char* uid_str, char* out_pin)
{
    char line[64];
    uint8_t found = 0;

    sd_spi_begin();

    if (f_open(&file, "uid.txt", FA_READ) == FR_OK)
    {
        while (f_gets(line, sizeof(line), &file))
        {
            line[strcspn(line, "\r\n")] = 0;

            char *sep = NULL;

            for (uint8_t i = 0; line[i] != '\0'; i++)
            {
                if (line[i] == ':')
                {
                    sep = &line[i];
                    break;
                }
            }

            if (sep)
            {
                *sep = '\0';

                if (strcmp(line, uid_str) == 0)
                {
                    strcpy(out_pin, sep + 1);

                    found = 1;

                    break;
                }
            }
        }

        f_close(&file);
    }

    sd_spi_end();

    return found;
}

/* =========================================================
 * REGISTER CARD
 * ========================================================= */

uint8_t register_card(const char* uid_str, const char* pin)
{
    FRESULT res;
    char buf[40];
    UINT bw;

    sd_spi_begin();

    res = f_open(&file, "uid.txt", FA_WRITE | FA_OPEN_APPEND);

    if (res == FR_OK)
    {
        sprintf(buf, "%s:%s\r\n", uid_str, pin);

        res = f_write(&file, buf, strlen(buf), &bw);

        f_close(&file);
    }

    sd_spi_end();

    return (res == FR_OK);
}

/* =========================================================
 * CHANGE PIN
 * ========================================================= */

uint8_t change_pin(const char* uid_str, const char* new_pin)
{
    char all_lines[10][32];

    uint8_t count = 0;
    uint8_t found = 0;

    FRESULT res;
    UINT bw;

    sd_spi_begin();

    res = f_open(&file, "uid.txt", FA_READ);

    if (res != FR_OK)
    {
        sd_spi_end();
        return 0;
    }

    while (count < 10 &&
           f_gets(all_lines[count], 32, &file))
    {
        all_lines[count][strcspn(all_lines[count], "\r\n")] = 0;

        count++;
    }

    f_close(&file);

    for (uint8_t i = 0; i < count; i++)
    {
        char *sep = NULL;

        for (uint8_t j = 0; all_lines[i][j] != '\0'; j++)
        {
            if (all_lines[i][j] == ':')
            {
                sep = &all_lines[i][j];
                break;
            }
        }

        if (sep)
        {
            *sep = '\0';

            if (strcmp(all_lines[i], uid_str) == 0)
            {
                sprintf(all_lines[i], "%s:%s",
                        uid_str,
                        new_pin);

                found = 1;
            }
            else
            {
                *sep = ':';
            }
        }
    }

    if (!found)
    {
        sd_spi_end();
        return 0;
    }

    res = f_open(&file,
                 "uid.txt",
                 FA_WRITE | FA_CREATE_ALWAYS);

    if (res != FR_OK)
    {
        sd_spi_end();
        return 0;
    }

    for (uint8_t i = 0; i < count; i++)
    {
        char line_buf[40];

        sprintf(line_buf,
                "%s\r\n",
                all_lines[i]);

        f_write(&file,
                line_buf,
                strlen(line_buf),
                &bw);
    }

    f_close(&file);

    sd_spi_end();

    return 1;
}

/* =========================================================
 * MENU
 * ========================================================= */

void show_menu(const char* uid_str)
{
    while(1)
    {
        lcd_command(0x01);

        lcd_print("1:Unlock 2:PIN");

        lcd_command(0xC0);

        lcd_print("3:Logout");

        char key = 0;

        while(key == 0)
        {
            key = keypad_getkey();

            delay_ms(50);
        }

        if (key == '1')
        {
            lcd_command(0x01);

            lcd_print("Door Open");

            servo_unlock();

            delay_ms(5000);

            lcd_command(0x01);

            lcd_print("Door Locked");

            servo_lock();

            delay_ms(1000);
        }
        else if (key == '2')
        {
            char new_pin[16];
            char confirm_pin[16];

            lcd_command(0x01);

            lcd_print("New PIN:");

            lcd_command(0xC0);

            input_from_keypad(new_pin, 4, 0);

            lcd_command(0x01);

            lcd_print("Confirm PIN:");

            lcd_command(0xC0);

            input_from_keypad(confirm_pin, 4, 0);

            if (strcmp(new_pin, confirm_pin) != 0)
            {
                lcd_command(0x01);

                lcd_print("PIN Mismatch!");
            }
            else if (change_pin(uid_str, new_pin))
            {
                lcd_command(0x01);

                lcd_print("PIN Changed!");
            }
            else
            {
                lcd_command(0x01);

                lcd_print("Change Failed!");
            }

            delay_ms(2000);
        }
        else if (key == '3')
        {
            lcd_command(0x01);

            lcd_print("Logging out");

            servo_lock();

            delay_ms(1000);

            while(keypad_getkey() != 0);

            break;
        }

        while(keypad_getkey() != 0);
    }
}

/* =========================================================
 * MAIN
 * ========================================================= */

int main(void)
{
    timer0_init();

    sei();

    lcd_init();

    keypad_init();

    spi_init();

    servo_init();

    /* Lock once at startup */
    servo_lock();

    /* SD Card Init */
    sdcard_init();

    sdcard_deselect();

    sd_spi_init();

    lcd_command(0x01);

    lcd_print("System Loading");

    sd_spi_begin();
    delay_ms(100);
    FRESULT mount_res = f_mount(&fs, "", 1);

    sd_spi_end();

    if (mount_res != FR_OK)
    {
        lcd_command(0x01);

        char m_err[16];
        sprintf(m_err, "Mnt Err: %d", (int)mount_res);
        lcd_print(m_err);

       
    }

    /* RFID Init */
    mfrc522_init();

    uint8_t status;
    uint8_t str[MAX_LEN];

    char uid_str[16];
    char stored_pin[16];
    char input_buf[16];

    while(1)
    {
        lcd_command(0x01);

        lcd_print("Scan Card");

        lcd_command(0xC0);

        lcd_print("Ready...");

        /* Wait RFID */
        while(1)
        {
            status = mfrc522_request(PICC_REQIDL, str);

            if (status == 0)
            {
                status = mfrc522_anticoll(str);

                if (status == 0)
                {
                    /* BCC check: byte[4] must equal XOR of byte[0..3] */
                    uint8_t bcc = str[0] ^ str[1] ^ str[2] ^ str[3];

                    if (bcc == str[4] && str[0] != 0x93)
                        break;
                }
            }

            delay_ms(100);
        }

        sprintf(uid_str,
                "%02X%02X%02X%02X",
                str[0],
                str[1],
                str[2],
                str[3]);

        lcd_command(0x01);

        lcd_print("Card Detected");

        lcd_command(0xC0);

        lcd_print(uid_str);

        delay_ms(1500);

        /* Registered Card */
        if (find_uid_and_pin(uid_str, stored_pin))
        {
            lcd_command(0x01);

            lcd_print("Enter PIN:");

            lcd_command(0xC0);

            input_from_keypad(input_buf, 4, 1);

            if (strcmp(input_buf, stored_pin) == 0)
            {
                lcd_command(0x01);

                lcd_print("Access Granted");

                servo_unlock();

                delay_ms(1000);

                show_menu(uid_str);
            }
            else
            {
                lcd_command(0x01);

                lcd_print("Invalid PIN");

                delay_ms(2000);
            }
        }
        else
        {
            lcd_command(0x01);

            lcd_print("Unregistered");

            lcd_command(0xC0);

            lcd_print("Admin Pass:");

            delay_ms(1000);

            lcd_command(0xC0);

            input_from_keypad(input_buf, 4, 1);

            if (strcmp(input_buf, ADMIN_PASSWORD) == 0)
            {
                lcd_command(0x01);

                lcd_print("Set New PIN");

                lcd_command(0xC0);

                input_from_keypad(input_buf, 4, 0);

                if (register_card(uid_str, input_buf))
                {
                    lcd_command(0x01);

                    lcd_print("Card Saved");
                }
                else
                {
                    lcd_command(0x01);

                    lcd_print("Save Failed");
                }
            }
            else
            {
                lcd_command(0x01);

                lcd_print("Access Denied");
            }

            delay_ms(2000);
        }

        /* Re-init RFID */
        mfrc522_init();
    }
}