/**
 * @file GPIO.h
 * 
 * @brief `AVRaffic Light` Project: General Purpose Input/Output Abstraction Layer
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date 03-02-2026
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct GPIO_t
{
    volatile uint8_t* port; // Data Register
    volatile uint8_t* ddr;  // Data Direction Register
    volatile uint8_t* pin;  // Input Pins Register
    uint8_t bit;            // Register Bit
} GPIO_t;

static inline void GPIO_setOutput(GPIO_t gpio)
{
    // Set Data Direction Register Bit to 1
    *(gpio.ddr) |= (1 << gpio.bit);
}

static inline void GPIO_setInput(GPIO_t gpio,bool pullup)
{
    // Set Data Direction Register Bit to 0
    *(gpio.ddr) &= ~(1 << gpio.bit);

    // Enable/Disable Pullup Resistor
    *(gpio.port) = (*(gpio.port) & ~(1 << gpio.bit)) | (pullup << gpio.bit);
}

static inline void GPIO_writeHigh(GPIO_t gpio)
{
    // Set Data Register Bit to 1
    *(gpio.port) |= (1 << gpio.bit);
}

static inline void GPIO_writeLow(GPIO_t gpio)
{
    // Set Data Register Bit to 0
    *(gpio.port) &= ~(1 << gpio.bit);
}

static inline void GPIO_toggle(GPIO_t gpio)
{
    // Toggle Data Register Bit
    *(gpio.port) ^= (1 << gpio.bit);
}

static inline uint8_t GPIO_read(GPIO_t gpio)
{
    // Return Input Pins Register Bit Value
    return (*(gpio.pin) & (1 << gpio.bit)) ? 1 : 0;
}