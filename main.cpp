/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"

/* TCS34725 color driver by Jan-Willem Smaal <usenet@gispen.org>  */
#include "color_tcs34725.h" 

// Default is 9600 8N1  This is a global  
Serial pc(USBTX, USBRX, "Color", 38400); // tx, rx 


// Blinking rate in milliseconds
#define RATE_MS 24


int main()
{
    Color color; 
    color.setIntegration(INT_24MS );
    color.setGain(GAIN_16X);

 
    pc.printf("C %5.5u R %5.5u G %5.5u B %5.5u\n", 
                color.c, 
                color.r, 
                color.g,
                color.b );

    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    DigitalOut led20(P0_20);

    led20 = 0; 

    while (true) {
        led = !led;
        
        led20 = 1;
        thread_sleep_for(RATE_MS*2);
        pc.printf("C %5.5u R %5.5u G %5.5u B %5.5u\n", 
                color.getC(), 
                color.getR(), 
                color.getG(),
                color.getB() );
        led20 = 0;
        thread_sleep_for(RATE_MS*2);
    }
}
