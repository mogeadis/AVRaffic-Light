/**
 * @file PWM.c
 * 
 * @brief `AVRaffic Light` Project: Pulse Width Modulation Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#include "PWM.h"

#include <avr/io.h>
#include <stdint.h>

void PWM_init(void)
{
    // Configure Fast PWM Mode
    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    TCCR2A |= (1 << WGM20) | (1 << WGM21);

    // Configure Non-Inverting Mode
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1);

    // Set Prescaler to 64 (16MHz/(64*256) ~= 976Hz)
    TCCR0B |= (1 << CS01) | (1 << CS00);
    TCCR2B |= (1 << CS21) | (1 << CS20);
}

void PWM_setDutyCycle(PWM_t* pwm,uint8_t value)
{
    if(value != 0)
    {
        // Enable PWM
        *(pwm->tccra) |= (1 << pwm->com);
    
        // Write Duty Cycle Value
        *(pwm->ocr) = value;
    }
    else
    {
        // Disable PWM
        *(pwm->tccra) &= ~(1 << pwm->com);
        // (Keep OCR Value)
        // (Set GPIO to LOW Externally)
    }
}