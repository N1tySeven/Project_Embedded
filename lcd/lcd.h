#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_print(const char *str);

#endif