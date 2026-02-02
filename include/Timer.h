/**
 * @file Timer.h
 * 
 * @brief `AVRaffic Light` Project: Timer Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date 03-02-2026
 */

#pragma once

#include <stdint.h>

void Timer_init(void);
uint32_t Timer_ms(void);