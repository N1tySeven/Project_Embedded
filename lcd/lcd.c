#include "lcd.h"
#include "../utils/delay.h"

static void lcd_commit()
{
    PORTB |= (1 << PB7);
    delay_ms(1);

    PORTB &= ~(1 << PB7);
    delay_ms(1);
}

void lcd_command(uint8_t cmd)
{
    PORTB &= ~(1 << PB6);

    PORTC &= 0xF0;
    PORTC |= (cmd >> 4);
    lcd_commit();

    PORTC &= 0xF0;
    PORTC |= (cmd & 0x0F);
    lcd_commit();
}

void lcd_data(uint8_t data)
{
    PORTB |= (1 << PB6);

    PORTC &= 0xF0;
    PORTC |= (data >> 4);
    lcd_commit();

    PORTC &= 0xF0;
    PORTC |= (data & 0x0F);
    lcd_commit();
}

void lcd_print(const char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

void lcd_init(void)
{
    DDRC |= 0x0F;

    DDRB |= (1 << PB6);
    DDRB |= (1 << PB7);

    delay_ms(20);

    lcd_command(0x33);
    lcd_command(0x32);
    lcd_command(0x28);

    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);

    delay_ms(2);
}