/**
 * @file Timer.c
 * 
 * @brief `AVRaffic Light` Project: Timer Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date 03-02-2026
 */

#include "Timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile static uint32_t MS_COUNTER = 0;

ISR(TIMER1_COMPA_vect)
{
    // Increment Counter
    MS_COUNTER++;
}

void Timer_init(void)
{
    // Configure CTC Mode
    TCCR1B |= (1 << WGM12);
    
    // Set Prescaler to 64 (16MHz/64 = 250kHz)
    TCCR1B |= (1 << CS11) | (1 << CS10);
    
    // Set Compare Value for 1ms Interrupts (250 ticks/ms)
    OCR1A = 250 - 1;
    
    // Enable Compare Interrupt
    TIMSK1 |= (1 << OCIE1A);
    
    // Enable Global Interrupts
    sei();
}

uint32_t Timer_ms(void)
{
    // Disable Global Interrupts
    cli();

    // Read Current Counter Value
    uint32_t ms_counter = MS_COUNTER;

    // Enable Global Interrupts
    sei();

    // Return Counter Value
    return ms_counter;
}