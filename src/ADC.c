/**
 * @file ADC.c
 * 
 * @brief `AVRaffic Light` Project: Analog-to-Digital Converter Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#include "ADC.h"

#include <avr/io.h>
#include <stdint.h>

void ADC_init(void)
{
    // Select AVcc as Voltage Reference
    ADMUX |= (1 << REFS0);

    // Enable ADC
    ADCSRA |= (1 << ADEN);
    
    // Set Prescaler to 128 (16MHz/128 = 125kHz)
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_read(uint8_t channel)
{
    // Select ADC Input Channel
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    
    // Start Conversion Process
    ADCSRA |= (1 << ADSC);

    // Wait for Conversion Completion
    while(ADCSRA & (1 << ADSC));
    
    // Return 10-bit Converted Value
    return ADC;
}