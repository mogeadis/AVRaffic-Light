/**
 * @file Display.h
 * 
 * @brief `AVRaffic Light` Project: Display Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include "LED.h"

#include <stdint.h>

typedef struct Display_t
{
    LED_t a;
    LED_t b;
    LED_t c;
    LED_t d;
    LED_t e;
    LED_t f;
    LED_t g;
    LED_t dp;
    LED_t common_pin;
} Display_t;

void Display_init(Display_t* disp);
void Display_setDigit(Display_t* disp,uint8_t value);
void Display_setDecimalPoint(Display_t* disp,uint8_t active);