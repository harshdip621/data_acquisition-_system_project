
/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "adc.h"
#include "uart.h"

#define RL 10000.0f      // Load resistor in ohms (10kΩ)
#define VCC 5.0f         // Supply voltage

#define A 272.4f        // MQ-135 curve constant for CO2 
#define B -2.718f        // MQ-135 curve exponent for CO2 

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU not initialized. Please initialize the FPU."
#endif




int main(void) {
    UartInit(9600);
    UartPuts("MQ-135 Gas Sensor\r\n");
    AdcInit();
    uint16_t adcVal = AdcRead();
    float Vout = ((float)adcVal / 4095.0f) * VCC;
    if (Vout <= 0.0f) Vout = 0.001f;
    float Rs = RL * (VCC - Vout) / Vout;
    float R0=Rs/3.7f;
    while (1) {
        char str[64];
         adcVal = AdcRead();

         Vout = ((float)adcVal / 4095.0f) * VCC;
        if (Vout <= 0.0f) Vout = 0.001f;

         Rs = RL * (VCC - Vout) / Vout;
        float ratio = Rs / R0;


        float ppm = A * pow(ratio, B);

        sprintf(str, "ADC=%d, V=%.2fV, Rs=%.1fΩ, CO2=%.1f ppm\r\n", adcVal, Vout, Rs, ppm);
        UartPuts(str);

        DelayMs(1000);
    }
}




