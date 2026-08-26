/**
 * @file Button.h
 * 
 * @brief `AVRaffic Light` Project: Button Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include "GPIO.h"

#include <stdbool.h>
#include <stdint.h>

typedef void (*ButtonCallback_t)(void* target);
typedef struct Button_t
{
    GPIO_t gpio;
    uint8_t raw_state;
    uint8_t stable_state;
    uint32_t last_debounce_time;
    bool change_detected;
    ButtonCallback_t on_press;
    ButtonCallback_t on_release;
    void* target;
} Button_t;

void Button_init(Button_t* button,GPIO_t gpio,ButtonCallback_t on_press,ButtonCallback_t on_release,void* target);
void Button_update(Button_t* button,uint32_t now);