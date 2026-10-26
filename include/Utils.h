/**
 * @file Utils.h
 * 
 * @brief `AVRaffic Light`: Utility Functions
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include "config.h"

#include <stdint.h>

static inline uint16_t Utils_mapRange(uint16_t x,uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2)
{
    // Check Input Value Range
    if(x <= x1)
    {
        // Return Lower Limit
        return y1;
    }
    else if(x >= x2)
    {
        // Return Upper Limit
        return y2;
    }
    else
    {
        // Return Mapped Value
        return (uint32_t)(x - x1)*(y2 - y1)/(x2 - x1) + y1;
    }
}

static inline uint8_t Utils_potToPWM(uint16_t value)
{
    // Return Mapped PWM Value
    return (uint8_t)Utils_mapRange(value,POT_DEADZONE,POT_MAX_VALUE - POT_DEADZONE,0,PWM_MAX_VALUE);
}