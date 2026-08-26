/**
 * @file Potentiometer.h
 * 
 * @brief `AVRaffic Light` Project: Potentiometer Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include "GPIO.h"

#include <stdint.h>

typedef struct Potentiometer_t
{
    GPIO_t gpio;
    uint8_t channel;
    uint16_t value;
} Potentiometer_t;

void Potentiometer_init(Potentiometer_t* pot,GPIO_t gpio,uint8_t channel);
void Potentiometer_update(Potentiometer_t* pot);