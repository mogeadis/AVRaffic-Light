/**
 * @file TrafficLight.h
 * 
 * @brief `AVRaffic Light` Project: Traffic Light Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include "Display.h"
#include "LED.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct TrafficLight_t
{
    LED_t red;
    LED_t orange;
    LED_t green;
    Display_t disp;
    uint8_t state;
    uint32_t state_duration;
    uint32_t last_change_time; 
    uint8_t displayed_value;
    uint8_t brightness;
    bool button_pressed;
    bool button_released;
} TrafficLight_t;

void TrafficLight_init(TrafficLight_t* tl);
void TrafficLight_update(TrafficLight_t* tl,uint32_t now);
void TrafficLight_setBrightness(TrafficLight_t* tl,uint32_t value);
void TrafficLight_handleButtonPress(void* target);
void TrafficLight_handleButtonRelease(void* target);