/**
 * @file LED.h
 * 
 * @brief `AVRaffic Light`: LED Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include "GPIO.h"
#include "PWM.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct LED_t
{
    GPIO_t gpio;
    uint8_t state;
    PWM_t pwm;
    bool has_pwm;
    uint8_t brightness;
} LED_t;

void LED_init(LED_t* led,GPIO_t gpio);
void LED_initPWM(LED_t* led,GPIO_t gpio,PWM_t pwm);
void LED_setOn(LED_t* led);
void LED_setOff(LED_t* led);
void LED_toggle(LED_t* led);
void LED_setBrightness(LED_t* led,uint8_t value);