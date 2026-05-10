#ifndef MFRC522_H
#define MFRC522_H

#include <avr/io.h>
#include <stdint.h>

#define MAX_LEN 16

#define PICC_REQIDL     0x26
#define PICC_ANTICOLL   0x93

void mfrc522_init(void);

uint8_t mfrc522_request(uint8_t reqMode, uint8_t *TagType);

uint8_t mfrc522_anticoll(uint8_t *serNum);

uint8_t mfrc522_get_version(void);

#endif