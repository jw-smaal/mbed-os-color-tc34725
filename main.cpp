/**
* @file main.cpp
* @brief Implementation of the TCS34725 chip for ARM embed projects
* @author Jan-Willem Smaal  <usenet@gispen.org>
* @date 7/16/2020 
*/
#include "mbed.h"
#include "platform/mbed_thread.h"

// TCS34725 color driver by Jan-Willem Smaal <usenet@gispen.org>  
#include "color_tcs34725.h" 

// Default is 9600 8N1  This is a global  
Serial pc(USBTX, USBRX, "Color", 38400); // tx, rx 

// Blinking rate in milliseconds we adjust to the actual 
// integration time of the sensor below. 
#define RATE_MS 24


int main()
{
    // Setup Color sensor  
    Color color; 
    color.setIntegration(INT_24MS );
    color.setGain(GAIN_16X);


    // Outputs:  
    DigitalOut led(LED1);

    // Pin20 is connected to the lighting bright LED on the sensor board. 
    DigitalOut sensorLed(P0_0);
    sensorLed = 0; 

    // Inputs:
    BusIn buttons(BUTTON1, BUTTON2, BUTTON3, BUTTON4);
    buttons.mode(PullUp);

    BusOut keyCol(P0_12, P0_13, P0_14, P0_15); 
    BusIn  keyRow(P0_16, P0_17, P0_18, P0_19); 
    keyRow.mode(PullNone);

    keyCol[0] = 1;
    keyCol[1] = 0;   
    keyCol[2] = 0;
    keyCol[3] = 0;
            

    AnalogIn sensor(P0_1); 

  
 
    while (true) {
        led = !led;
        
        sensorLed = 1;
        thread_sleep_for(RATE_MS*2);

        // Activate Colums based on ButtonState 
        keyCol = ~buttons.read();

        pc.printf("C %5.5u R %5.5u G %5.5u B %5.5u W %5.5u K %2.2X keyCol %2.2X\n", 
                color.getC(), 
                color.getR(), 
                color.getG(),
                color.getB(),
                sensor.read_u16(),
                keyRow.read(),
                keyCol.read()
        );
        sensorLed = 0;
        thread_sleep_for(RATE_MS*2);
    }
}

/* EOF main.cpp */