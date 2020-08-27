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
#include <string.h>

#define TWELVEHOURS 43200
#define PIN  24

unsigned char GetPortValue()
{
    switch(GetMoonState())
    {
        case NEW: 
            printf("Phase: NEW");
            return (0<<GPIO06)|(0<<GPIO13)|(0<<GPIO19)|(0<<GPIO26);
        case WANINGCRESCENT: 
            printf("Phase: WANINGCRESCENT");
            return (1<<GPIO06)|(0<<GPIO13)|(0<<GPIO19)|(0<<GPIO26);
        case THIRDQTR: 
            printf("Phase: THIRDQTR");
            return (1<<GPIO06)|(1<<GPIO13)|(0<<GPIO19)|(0<<GPIO26);
        case WANINGGIBBOUS: 
            printf("Phase: WANINGGIBBOUS");
            return (1<<GPIO06)|(1<<GPIO13)|(1<<GPIO19)|(0<<GPIO26);
        case FULL: 
            printf("Phase: FULL");
            return (1<<GPIO06)|(1<<GPIO13)|(1<<GPIO19)|(1<<GPIO26);
        case WAXINGGIBBOUS: 
            printf("Phase: WAXINGGIBBOUS");
            return (0<<GPIO06)|(1<<GPIO13)|(1<<GPIO19)|(1<<GPIO26);
        case FIRSTQTR: 
            printf("Phase: FIRSTQTR");
            return (0<<GPIO06)|(0<<GPIO13)|(1<<GPIO19)|(1<<GPIO26);
        case WAXINGCRESCENT: 
            printf("Phase: WAXINGCRESCENT");
            return (0<<GPIO06)|(0<<GPIO13)|(0<<GPIO19)|(1<<GPIO26);
    }
}

int main(int argc, char *argv[])
{
    char param[100];
    if(argc > 1) strcpy(param,argv[1]);
    else strcpy(param,"");
    
    printf("Argument passed: %s\n", param);
    if(strcmp("--demo",param) == 0)
    {
        printf("Initiating demo sequence\n");
        // This is not setting the array correctly 
        int gpioArray[4] = { GPIO06NUM, GPIO13NUM, GPIO19NUM, GPIO26NUM };

        printf("Size of gpioArray is %d\n", sizeof(gpioArray) / sizeof(gpioArray[0]));
        for (int i = 0; i < sizeof(gpioArray) / sizeof(gpioArray[0]); i++)
        {
            disable_pins(gpioArray[i]); // Reset
            init_gpio(gpioArray[i]); // Initiliaze array
            set_output(gpioArray[i]); // set gpio pin to output
        }

        int i = 0;
        while (1)
        {
            // RPIPORT = GetPortValue();

            // // I think this can be a thread
            // Set_Port(); // Assign output pins 

            // sleep(TWELVEHOURS);

            // Demo
            switch (i)
            {
            case 0:
                RPIPORT = 0x01 << 0;
                i = i + 1;
                break;

            case 1:
                RPIPORT = 0x01 << 1;
                i = i + 1;
                break;

            case 2:
                RPIPORT = 0x01 << 2;
                i = i + 1;
                break;

            case 3:
                RPIPORT = 0x01 << 3;
                i = 0;
                break;

            default:
                RPIPORT = 0x0F;
                break;
            }
            Set_Port();
            sleep(1);
        }
        return(0);
    }
    else if(strcmp("--disable-pins",param) == 0)
    {
        printf("Initiating disable-pins sequence\n");
        // This is not setting the array correctly 
        int gpioArray[4] = { GPIO06NUM, GPIO13NUM, GPIO19NUM, GPIO26NUM };

        printf("Size of gpioArray is %d\n", sizeof(gpioArray) / sizeof(gpioArray[0]));
        for (int i = 0; i < sizeof(gpioArray) / sizeof(gpioArray[0]); i++)
        {
            disable_pins(gpioArray[i]); // Reset
        }
        return(0);
    }
    else
    {
        printf("Initiating Moonphase sequence\n");
        // This is not setting the array correctly 
        int gpioArray[4] = { GPIO06NUM, GPIO13NUM, GPIO19NUM, GPIO26NUM };

        printf("Size of gpioArray is %d\n", sizeof(gpioArray) / sizeof(gpioArray[0]));
        for (int i = 0; i < sizeof(gpioArray) / sizeof(gpioArray[0]); i++)
        {
            disable_pins(gpioArray[i]); // Reset
            init_gpio(gpioArray[i]); // Initiliaze array
            set_output(gpioArray[i]); // set gpio pin to output
        }

        // init_gpio(PIN);
        // set_output(PIN);
        // I am going to use a char
        // I want to use 4 bits to represent the phases
        RPIPORT = 0x0F; // Right most bits will be the bits I care about

        // STEPS
        // 1 - Get Fractional
        // 2 - Determine which phase by fractional 
        // 3 - Assign GPIO pins
        int i = 0;
        while (1)
        {
            RPIPORT = GetPortValue();

            // // I think this can be a thread
            Set_Port(); // Assign output pins

            sleep(TWELVEHOURS);

        }
        return(0);
    }
    return(0);
}
