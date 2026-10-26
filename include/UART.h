/**
 * @file UART.h
 * 
 * @brief `AVRaffic Light`: Universal Asynchronous Receiver/Transmitter Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include <stdint.h>

void UART_init(uint32_t baud_rate);
void UART_sendByte(uint8_t data);
void UART_printString(const char* str);
void UART_printInt(uint32_t value);