/*
 * Is this sending serial data?
 * Use the gpio numbers
 * 
 * Notes:
 *      - Every new moon is 29.53 days
 * 
 * The gpio pins will be turning on the LED lights
 */

#include "RpiGPIO.h"
#include "moonphase.h"
#include <stdio.h>   

// GPIO pins
#define GPIO06 6
#define GPIO13 13
#define GPIO19 19
#define GPIO26 26

#define 

int main(int argc, char *argv[])
{
        int gpioArray[4] = {GPIO06, GPIO13, GPIO19, GPIO26};

        for(int i = 0; i < sizeof(gpioArray); i++)
        {
                init_gpio(gpioArray[i]); // Initiliaze array
                set_output(gpioArray[i]); // set gpio pin to output
        }

        // I am going to use a char
        // I want to use 4 bits to represent the phases
        unsigned char IO = 0x00; // Right most bits will be the bits I care about

        // STEPS
        // 1 - Get Fractional
        // 2 - Determine which phase by fractional 
        // 3 - Assign GPIO pins
        while(1)
        {
                // _sleep(GetHours(10));
                _sleep(5);

                // Test output
                gpio_output(GPIO06,~IO);
        }

        return(0);
}
