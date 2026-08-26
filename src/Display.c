/**
 * @file Display.c
 * 
 * @brief `AVRaffic Light` Project: Display Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#include "Display.h"
#include "config.h"
#include "LED.h"

#include <stdint.h>

#define NUM_SEGMENTS 7

static const uint8_t SEGMENT_STATE_MAP[10] =
{
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

static inline void setSegment(LED_t* led,uint8_t active)
{
    // Inverse State for Common Anode Display
    #if !COMMON_CATHODE_DISPLAY
        active = !active;
    #endif

    // Check State
    if(active)
    {
        // Set Segment LED to ON
        LED_setOn(led);
    }
    else
    {
        // Set Segment LED to OFF
        LED_setOff(led);
    }
}

void Display_init(Display_t* disp)
{
    // Initialize LEDs
    LED_init(&disp->a,GPIO_LED_A);
    LED_init(&disp->b,GPIO_LED_B);
    LED_init(&disp->c,GPIO_LED_C);
    LED_init(&disp->d,GPIO_LED_D);
    LED_init(&disp->e,GPIO_LED_E);
    LED_init(&disp->f,GPIO_LED_F);
    LED_init(&disp->g,GPIO_LED_G);
    LED_init(&disp->dp,GPIO_LED_DP);
    LED_initPWM(&disp->common_pin,GPIO_COMMON_PIN,PWM_COMMON_PIN);
}

void Display_setDigit(Display_t* disp,uint8_t value)
{
    // Check Digit Value
    if(value <= 9)
    {
        // Retrieve Segment States & LEDs
        uint8_t segment_states = SEGMENT_STATE_MAP[value];
        LED_t* leds[NUM_SEGMENTS] =
        {
            &disp->a,
            &disp->b,
            &disp->c,
            &disp->d,
            &disp->e,
            &disp->f,
            &disp->g
        };

        // Set Segment LED States
        for(int index = 0; index < NUM_SEGMENTS; index++)
        {
            setSegment(leds[index],segment_states & (1 << index));
        }
    }
}

void Display_setDecimalPoint(Display_t* disp,uint8_t active)
{
    // Set Decimal Point LED to ON/OFF
    setSegment(&disp->dp,active);
}