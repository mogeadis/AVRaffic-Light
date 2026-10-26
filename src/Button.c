/**
 * @file Button.c
 * 
 * @brief `AVRaffic Light`: Button Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#include "Button.h"
#include "config.h"
#include "GPIO.h"
#include "UART.h"

#include <stdbool.h>
#include <stdint.h>

void Button_init(Button_t* btn,GPIO_t gpio,ButtonCallback_t on_press,ButtonCallback_t on_release,void* target)
{
    // Assign Initialization Variables
    btn->gpio = gpio;
    btn->on_press = on_press;
    btn->on_release = on_release;
    btn->target = target;
    btn->last_debounce_time = 0;
    btn->change_detected = false;

    // Set GPIO as Input with Pullup Resistor
    GPIO_setInput(gpio,true);

    // Set Input States to Current Reading
    btn->raw_state = GPIO_read(gpio);
    btn->stable_state = btn->raw_state;
}

void Button_update(Button_t* btn,uint32_t now)
{
    // Clear Change Detection Flag
    btn->change_detected = false;

    // Read GPIO State
    uint8_t raw_state = GPIO_read(btn->gpio);

    // Check Raw State Change
    if(raw_state != btn->raw_state)
    {
        // Update Raw State & Debounce Time
        btn->raw_state = raw_state;
        btn->last_debounce_time = now;
    }

    // Check Debounce Duration
    if((now - btn->last_debounce_time) >= BUTTON_DEBOUNCE_DURATION)
    {
        // Check Stable State Change
        if(btn->stable_state != btn->raw_state)
        {
            // Update Stable State & Change Detection Flag
            btn->stable_state = btn->raw_state;
            btn->change_detected = true;

            // Check Stable State
            if(btn->stable_state == 0)
            {
                // Debug Button Press
                #if DEBUG
                    UART_printString("Button Pressed!\r\n");
                #endif
                
                // Invoke Button Press Callback
                if(btn->on_press)
                {
                    btn->on_press(btn->target);
                }
            }
            else
            {
                // Debug Button Release
                #if DEBUG
                    UART_printString("Button Released!\r\n");
                #endif

                // Invoke Button Release Callback
                if(btn->on_release)
                {
                    btn->on_release(btn->target);
                }
            }
        }
    }
}