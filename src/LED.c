/**
 * @file LED.c
 * 
 * @brief `AVRaffic Light` Project: LED Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date 03-02-2026
 */

#include "LED.h"
#include "CONFIG.h"
#include "GPIO.h"
#include "PWM.h"

#include <stdbool.h>
#include <stdint.h>

void LED_init(LED_t* led,GPIO_t gpio)
{
    // Assign Initialization Variables
    led->gpio = gpio;
    led->has_pwm = false;

    // Set GPIO as Output
    GPIO_setOutput(led->gpio);

    // Set LED to OFF
    LED_setOff(led);
}

void LED_initPWM(LED_t* led,GPIO_t gpio,PWM_t pwm)
{
    // Assign Initialization Variables
    led->gpio = gpio;
    led->pwm = pwm;
    led->has_pwm = true;

    // Set GPIO as Output
    GPIO_setOutput(led->gpio);

    // Set LED to OFF
    LED_setOff(led);
}

void LED_setOn(LED_t* led)
{
    // Check PWM Functionality
    if(led->has_pwm)
    {
        // Set LED Brightness to Max
        LED_setBrightness(led,PWM_MAX_VALUE);
    }
    else
    {
        // Set GPIO to HIGH
        GPIO_writeHigh(led->gpio);

        // Update LED State & Brightness
        led->state = 1;
        led->brightness = PWM_MAX_VALUE;
    }
}

void LED_setOff(LED_t* led)
{
    // Check PWM Functionality
    if(led->has_pwm)
    {
        // Set LED Brightness to 0
        LED_setBrightness(led,0);
    }
    else
    {
        // Set GPIO to LOW
        GPIO_writeLow(led->gpio);

        // Update LED State & Brightness
        led->state = 0;
        led->brightness = 0;
    }
}

void LED_toggle(LED_t* led)
{
    // Check PWM Functionality
    if(led->has_pwm)
    {
        // Toggle Brightness Value (Stored in OCR)
        uint8_t brightness = (led->brightness) ? 0 : *(led->pwm.ocr);
        
        // Set LED Brightness
        LED_setBrightness(led,brightness);
    }
    else
    {
        // Toggle GPIO State
        GPIO_toggle(led->gpio);

        // Update LED State & Brightness
        led->state = !led->state;
        led->brightness = (led->state) ? PWM_MAX_VALUE : 0;
    }
}

void LED_setBrightness(LED_t* led,uint8_t value)
{
    // Check PWM Functionality
    if(led->has_pwm)
    {
        // Set PWM Duty Cycle Value
        PWM_setDutyCycle(&led->pwm,value);

        // Check Special Value Case
        if(value == 0)
        {
            // Set GPIO State to LOW
            GPIO_writeLow(led->gpio);
        }
    }
    else
    {
        // Set GPIO State to HIGH/LOW
        value > 0 ? GPIO_writeHigh(led->gpio) : GPIO_writeLow(led->gpio);
    }

    // Update LED State & Brightness
    led->state = (value > 0);
    led->brightness = value;
}