/**
 * @file IRQ.c
 * 
 * @brief `AVRaffic Light`: Interrupt Request Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#include "IRQ.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile static bool IRQ_FLAG = false;

ISR(INT0_vect)
{
    // Set IRQ Flag to True
    IRQ_FLAG = true;
}

void IRQ_init()
{
    // Configure Logical Change Interrupt Mode
    EICRA = (1 << ISC00);

    // Enable External Interrupt
    EIMSK = (1 << INT0);

    // Enable Global Interrupts
    sei();
}

bool IRQ_pending()
{
    // Disable Global Interrupts
    cli();

    // Capture Current Flag Value
    bool irq_flag = IRQ_FLAG;

    // Enable Global Interrupts
    sei();

    // Return Flag Value
    return irq_flag;
}

void IRQ_reset()
{
    // Disable Global Interrupts
    cli();

    // Clear IRQ Flag
    IRQ_FLAG = false;

    // Enable Global Interrupts
    sei();
}