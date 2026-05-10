#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

extern volatile uint32_t ms_counting;

void delay_ms(uint32_t delay);

#endif