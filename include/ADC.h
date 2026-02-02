/**
 * @file ADC.h
 * 
 * @brief `AVRaffic Light` Project: Analog-to-Digital Converter Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date 03-02-2026
 */

#pragma once

#include <stdint.h>

void ADC_init(void);
uint16_t ADC_read(uint8_t channel);