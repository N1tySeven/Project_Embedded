#include "delay.h"

volatile uint32_t ms_counting = 0;

void delay_ms(uint32_t delay)
{
    uint32_t start = ms_counting;

    while((ms_counting - start) < delay);
}