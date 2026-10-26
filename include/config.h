/**
 * @file config.h
 * 
 * @brief `AVRaffic Light`: Configuration File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include "GPIO.h"
#include "PWM.h"

#include <avr/io.h>

// ------------------
// UART Configuration
// ------------------

#define DEBUG 1
#define BAUD_RATE 9600

// ---------------------------
// Traffic Light Configuration
// ---------------------------

#define STATE_DURATION_RED 9000
#define STATE_DURATION_ORANGE 3000
#define STATE_DURATION_GREEN 6000

// -----------------
// LED Configuration
// -----------------

#define GPIO_LED_RED (GPIO_t){&PORTD,&DDRD,&PIND,PD6}
#define GPIO_LED_ORANGE (GPIO_t){&PORTD,&DDRD,&PIND,PD5}
#define GPIO_LED_GREEN (GPIO_t){&PORTD,&DDRD,&PIND,PD3}

// ---------------------
// Display Configuration
// ---------------------

#define GPIO_LED_A (GPIO_t){&PORTD,&DDRD,&PIND,PD4}
#define GPIO_LED_B (GPIO_t){&PORTD,&DDRD,&PIND,PD7}
#define GPIO_LED_C (GPIO_t){&PORTB,&DDRB,&PINB,PB0}
#define GPIO_LED_D (GPIO_t){&PORTB,&DDRB,&PINB,PB1}
#define GPIO_LED_E (GPIO_t){&PORTB,&DDRB,&PINB,PB2}
#define GPIO_LED_F (GPIO_t){&PORTB,&DDRB,&PINB,PB4}
#define GPIO_LED_G (GPIO_t){&PORTC,&DDRC,&PINC,PC2}
#define GPIO_LED_DP (GPIO_t){&PORTB,&DDRB,&PINB,PB5}
#define GPIO_COMMON_PIN (GPIO_t){&PORTB,&DDRB,&PINB,PB3}
#define COMMON_CATHODE_DISPLAY 1

// -----------------
// PWM Configuration
// -----------------

#define PWM_LED_RED (PWM_t){&TCCR0A,&OCR0A,COM0A1}
#define PWM_LED_ORANGE (PWM_t){&TCCR0A,&OCR0B,COM0B1}
#define PWM_LED_GREEN (PWM_t){&TCCR2A,&OCR2B,COM2B1}
#define PWM_COMMON_PIN (PWM_t){&TCCR2A,&OCR2A,COM2A1}
#define PWM_MAX_VALUE 255

// --------------------
// Button Configuration
// --------------------

#define GPIO_BUTTON (GPIO_t){&PORTD,&DDRD,&PIND,PD2}
#define BUTTON_DEBOUNCE_DURATION 5

// ---------------------------
// Potentiometer Configuration
// ---------------------------

#define GPIO_POT (GPIO_t){&PORTC,&DDRC,&PINC,PC3}
#define POT_ADC_CHANNEL 3
#define POT_MAX_VALUE 1023
#define POT_DEADZONE 3