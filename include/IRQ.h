/**
 * @file IRQ.h
 * 
 * @brief `AVRaffic Light` Project: Interrupt Request Interface
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#pragma once

#include <stdbool.h>

void IRQ_init();
bool IRQ_pending();
void IRQ_reset();