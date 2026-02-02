/**
 * @file TrafficLight.c
 * 
 * @brief `AVRaffic Light` Project: Traffic Light Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date 03-02-2026
 */

#include "TrafficLight.h"
#include "CONFIG.h"
#include "Display.h"
#include "LED.h"
#include "Timer.h"
#include "UART.h"

#include <stdbool.h>
#include <stdint.h>

#define NUM_STATES 3

typedef enum TrafficLightState_t
{
    TL_RED,
    TL_ORANGE,
    TL_GREEN
} TrafficLightState_t;

static void applyState(TrafficLight_t* tl)
{
    // Set State Duration
    static const uint32_t durations[NUM_STATES] = {STATE_DURATION_RED,STATE_DURATION_ORANGE,STATE_DURATION_GREEN};
    tl->state_duration = durations[tl->state];
    
    // Set State LED Brightness
    LED_t* leds[NUM_STATES] = {&tl->red,&tl->orange,&tl->green};
    for(int index = 0; index < NUM_STATES; index++)
    {
        LED_setBrightness(leds[index],0);
    }
    LED_setBrightness(leds[tl->state],tl->brightness);
    
    // Debug State
    #if DEBUG
        static const char* states_str[NUM_STATES] = {"Red","Orange","Green"};
        const char* str = states_str[tl->state];
        UART_printString("\n");
        UART_printString(str);
        UART_printString(" Light!\r\n");
    #endif
}

void TrafficLight_init(TrafficLight_t* tl)
{
    // Initialize LEDs
    LED_initPWM(&tl->red,GPIO_LED_RED,PWM_LED_RED);
    LED_initPWM(&tl->orange,GPIO_LED_ORANGE,PWM_LED_ORANGE);
    LED_initPWM(&tl->green,GPIO_LED_GREEN,PWM_LED_GREEN);

    // Initialize Display
    tl->displayed_value = 0;
    Display_init(&tl->disp);
    Display_setDigit(&tl->disp,tl->displayed_value);

    // Initialize Default State
    tl->state = TL_RED;
    tl->last_change_time = Timer_ms();
    applyState(tl);

    // Assign Initialization Variables
    tl->brightness = tl->disp.common_pin.brightness;
    tl->button_pressed = false;
    tl->button_released = false;
}

void TrafficLight_update(TrafficLight_t* tl,uint32_t now)
{
    // Check Button-Pressed Flag
    if(tl->button_pressed)
    {
        // Check Current State
        if(tl->state == TL_RED)
        {
            // Proceed from RED to ORANGE State
            tl->state = TL_ORANGE;
            tl->last_change_time = now;
            applyState(tl);
        }

        // Set Decimal Point LED to ON
        Display_setDecimalPoint(&tl->disp,1);

        // Clear Button-Pressed Flag
        tl->button_pressed = false;
    }

    // Check Button-Released Flag
    if(tl->button_released)
    {
        // Set Decimal Point LED to ON
        Display_setDecimalPoint(&tl->disp,0);

        // Clear Button-Released Flag
        tl->button_released = false;
    }

    // Calculate Remaining State Duration
    uint32_t elapsed_time = now - tl->last_change_time;
    uint8_t remaining_duration = (tl->state_duration - elapsed_time + 999)/1000;
    
    // Check Remaining State Duration
    if(remaining_duration == 0)
    {
        // Proceed to Next State
        tl->state = (tl->state + 1) % NUM_STATES;
        tl->last_change_time = now;
        applyState(tl);

        // Recalculate Remaining Duration
        remaining_duration = tl->state_duration/1000;
    }

    // Check Remaining Duration Change
    if(remaining_duration != tl->displayed_value)
    {
        // Update Displayed Value
        tl->displayed_value = remaining_duration;
        Display_setDigit(&tl->disp,tl->displayed_value);

        // Debug Displayed Value
        #if DEBUG
            UART_printString("Countdown: ");
            UART_printInt(tl->displayed_value);
            UART_printString("\r\n");
        #endif
    }
}

void TrafficLight_setBrightness(TrafficLight_t* tl,uint32_t value)
{
    // Check Brightness Change
    if(value != tl->brightness)
    {
        // Update Brightness
        tl->brightness = value;

        // Set LED Brightness
        LED_t* leds[NUM_STATES] = {&tl->red,&tl->orange,&tl->green};
        LED_setBrightness(leds[tl->state],value);
    
        // Inverse Brightness for Common Cathode Display
        #if COMMON_CATHODE_DISPLAY
            value = PWM_MAX_VALUE - value;
        #endif

        // Set Display Brightness
        LED_setBrightness(&tl->disp.common_pin,value);
    }
}

void TrafficLight_handleButtonPress(void* target)
{
    // Set Button-Pressed Flag to True
    TrafficLight_t* tl = (TrafficLight_t*)target;
    tl->button_pressed = true;
}

void TrafficLight_handleButtonRelease(void* target)
{
    // Set Button-Released Flag to True
    TrafficLight_t* tl = (TrafficLight_t*)target;
    tl->button_released = true;
}