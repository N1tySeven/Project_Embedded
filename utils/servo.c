#include "servo.h"
#include "../utils/delay.h"

static uint8_t servo_state = 0; // 0 = stopped, 1 = locked, 2 = unlocked

static void servo_pwm_start(uint16_t pulse_width)
{
    OCR1A = pulse_width;
    TCNT1 = 0;
    // Connect OC1A to pin
    TCCR1A |= (1 << COM1A1);
}

static void servo_pwm_stop(void)
{
    // Disconnect OC1A from pin
    TCCR1A &= ~(1 << COM1A1);
    PORTB &= ~(1 << PB1);
}

void servo_init(void)
{
    // Set PB1 as output, drive LOW
    DDRB |= (1 << PB1);
    PORTB &= ~(1 << PB1);

    // Timer 1: Fast PWM, Mode 14 (TOP = ICR1)
    ICR1 = 20000;           // 50Hz
    OCR1A = SERVO_STOP_PW;  // Pre-load stop position

    TCCR1A = (1 << WGM11);  // PWM disconnected from pin
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8

    servo_state = 0;
}

void servo_stop(void)
{
    // Send stop signal briefly, then disconnect
    servo_pwm_start(SERVO_STOP_PW);
    delay_ms(60);
    servo_pwm_stop();
}

void servo_unlock(void)
{
    if (servo_state == 2) return; // Already unlocked

    // Rotate clockwise to open
    servo_pwm_start(SERVO_CW);
    delay_ms(SERVO_ROTATION_TIME_MS);

    // Stop the motor
    servo_pwm_start(SERVO_STOP_PW);
    delay_ms(60);
    servo_pwm_stop();

    servo_state = 2;
}

void servo_lock(void)
{
    if (servo_state == 1) return; // Already locked

    // Rotate counter-clockwise to close
    servo_pwm_start(SERVO_CCW);
    delay_ms(SERVO_ROTATION_TIME_MS);

    // Stop the motor
    servo_pwm_start(SERVO_STOP_PW);
    delay_ms(60);
    servo_pwm_stop();

    servo_state = 1;
}
