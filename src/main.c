/**
 * @file main.c
 * 
 * @brief `AVRaffic Light` Project: Main File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date February 2026
 */

#include "config.h"
#include "ADC.h"
#include "Button.h"
#include "IRQ.h"
#include "Potentiometer.h"
#include "PWM.h"
#include "Timer.h"
#include "TrafficLight.h"
#include "UART.h"
#include "Utils.h"

#include <stdint.h>

int main(void)
{
    // Initialize Hardware
    Timer_init();
    ADC_init();
    IRQ_init();
    PWM_init();
    UART_init(BAUD_RATE);
    
    // Initialize Traffic Light
    TrafficLight_t tl;
    TrafficLight_init(&tl);

    // Initialize Button
    Button_t btn;
    Button_init(&btn,GPIO_BUTTON,TrafficLight_handleButtonPress,TrafficLight_handleButtonRelease,&tl);

    // Initialize Potentiometer
    Potentiometer_t pot;
    Potentiometer_init(&pot,GPIO_POT,POT_ADC_CHANNEL);

    // Loop Indefinitely
    while(1)
    {
        // Update Potentiometer Reading
        Potentiometer_update(&pot);

        // Set Traffic Light Brightness
        uint8_t brightness = Utils_potToPWM(pot.value);
        TrafficLight_setBrightness(&tl,brightness);

        // Read Current System Time
        uint32_t now = Timer_ms();

        // Check External Interrupt Request
        if(IRQ_pending())
        {
            // Update Button Reading
            Button_update(&btn,now);

            // Check Button Change Detection
            if(btn.change_detected)
            {
                // Clear External Interrupt Request
                IRQ_reset();
            }
        }
        
        // Update Traffic Light State
        TrafficLight_update(&tl,now);
    }
}