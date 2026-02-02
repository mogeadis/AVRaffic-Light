/**
 * @file PWM.h
 * 
 * @brief `AVRaffic Light` Project: Pulse Width Modulation Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date 03-02-2026
 */

#pragma once

#include <stdint.h>

typedef struct PWM_t
{
    volatile uint8_t* tccra; // Timer/Counter Control Register A
    volatile uint8_t* ocr;   // Output Compare Register
    uint8_t com;             // Compare Output Mode Bit
} PWM_t;

void PWM_init(void);
void PWM_setDutyCycle(PWM_t* pwm,uint8_t value);