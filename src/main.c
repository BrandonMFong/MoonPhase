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
#include <unistd.h>


#define PIN  24

int main(int argc, char *argv[])
{
        // This is not setting the array correctly 
        int gpioArray[4] = {GPIO06NUM, GPIO13NUM, GPIO19NUM, GPIO26NUM};

        printf("Size of gpioArray is %d\n", sizeof(gpioArray)/sizeof(gpioArray[0]));
        for(int i = 0; i < sizeof(gpioArray)/sizeof(gpioArray[0]); i++)
        {
                // Reset
                printf("Deinitializing pin %d\n", gpioArray[i]);
                disable_pins(gpioArray[i]);
                printf("Initializing pin %d\n", gpioArray[i]);
                init_gpio(gpioArray[i]); // Initiliaze array
                set_output(gpioArray[i]); // set gpio pin to output
        }

        // init_gpio(PIN);
        // set_output(PIN);
        // I am going to use a char
        // I want to use 4 bits to represent the phases
        RPIPORT = 0x0A; // Right most bits will be the bits I care about

        // STEPS
        // 1 - Get Fractional
        // 2 - Determine which phase by fractional 
        // 3 - Assign GPIO pins
        while(1)
        {
                // _sleep(GetHours(10));
                sleep(1);

                RPIPORT = ~RPIPORT;

                Set_Port(); // Assign output pins 
        }

        return(0);
}
