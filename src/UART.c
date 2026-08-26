/**
 * @file UART.c
 * 
 * @brief `AVRaffic Light` Project: Universal Asynchronous Receiver/Transmitter Implementation
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#include "UART.h"

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

void UART_init(uint32_t baud_rate)
{
    // Set Baud Rate Register Bits
    uint16_t ubrr = (uint16_t)((F_CPU/(16UL*baud_rate)) - 1);
    UBRR0H = (uint8_t)((ubrr >> 8) & 0x0F);
    UBRR0L = (uint8_t)ubrr;

    // Enable Transmitter
    UCSR0B |= (1 << TXEN0);

    // Select 8-bit Character Size
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); 
}

void UART_sendByte(uint8_t data)
{
    // Wait for Data Register Availability
    while(!(UCSR0A & (1 << UDRE0)));

    // Write Byte to Data Register
    UDR0 = data;
}

void UART_printString(const char* str)
{
    // Loop Through String Characters
    while(*str)
    {
        // Print Current Character
        UART_sendByte(*str);

        // Move to Next Character
        str++;
    }
}

void UART_printInt(uint32_t value)
{
    // Allocate Character Buffer
    char buffer[12];

    // Convert Integer to ASCII String
    ultoa(value,buffer,10);

    // Print Character Buffer
    UART_printString(buffer);
}