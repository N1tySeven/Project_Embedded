#include "keypad.h"
#include "../utils/delay.h"

static char keys[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

void keypad_init(void)
{
    // ROWS
    DDRD |= 0xF0;

    // COLS
    DDRD &= ~((1 << PD0) | (1 << PD1) | (1 << PD2));

    DDRB &= ~(1 << PB0);
}

char keypad_getkey(void)
{
    for(int r = 0; r < 4; r++)
    {
        PORTD |= (1 << PD4) |
                 (1 << PD5) |
                 (1 << PD6) |
                 (1 << PD7);

        PORTD |= (1 << PD0) |
                 (1 << PD1) |
                 (1 << PD2);

        PORTB |= (1 << PB0);

        if(r == 0)
            PORTD &= ~(1 << PD7);

        else if(r == 1)
            PORTD &= ~(1 << PD6);

        else if(r == 2)
            PORTD &= ~(1 << PD5);

        else if(r == 3)
            PORTD &= ~(1 << PD4);

        delay_ms(5);

        if(!(PIND & (1 << PD0)))
            return keys[r][0];

        if(!(PIND & (1 << PD1)))
            return keys[r][1];

        if(!(PIND & (1 << PD2)))
            return keys[r][2];

        if(!(PINB & (1 << PB0)))
            return keys[r][3];
    }

    return 0;
}