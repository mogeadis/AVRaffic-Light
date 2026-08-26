/**
 * @file Potentiometer.c
 * 
 * @brief `AVRaffic Light` Project: Potentiometer Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#include "Potentiometer.h"
#include "ADC.h"
#include "GPIO.h"

#include <stdint.h>

void Potentiometer_init(Potentiometer_t* pot,GPIO_t gpio,uint8_t channel)
{
    // Assign Initialization Variables
    pot->gpio = gpio;
    pot->channel = channel;
    pot->value = 0;

    // Set GPIO as Input without Pullup Resistor
    GPIO_setInput(pot->gpio,false);
}

void Potentiometer_update(Potentiometer_t* pot)
{
    // Read ADC Channel Value
    pot->value = ADC_read(pot->channel);
}