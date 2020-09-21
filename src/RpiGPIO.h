/*
 * Is this sending serial data?
 * Use the gpio numbers
 */

#include "RPi_GPIO_Code_Samples.h"
#include <stdbool.h>
#include <pthread.h>

// GPIO pin number
#define GPIO06NUM 6
#define GPIO13NUM 13
#define GPIO19NUM 19
#define GPIO26NUM 26

// From left to right
#define GPIO06 3
#define GPIO13 2
#define GPIO19 1
#define GPIO26 0



/*
 * Enable GPIO pins
 */
void init_gpio(int pin)
{
        printf("Initializing pin %d\n", pin);
	if (-1 == GPIOExport(pin)) 
        {
		fprintf(stderr, "[Init] Error for pin %d\n", pin);
                exit(-1);
        }
}

/*
 * Disable GPIO pins
 */
void disable_pins(int pin)
{
        printf("Deinitializing pin %d\n", pin);
	if (-1 == GPIOUnexport(pin)) 
        {
		fprintf(stderr, "[Exit] Error for pin %d\n", pin);
                exit(-1);
        }
}

/*
 * Set GPIO directions
 */
void set_input(int pin)
{
	if (-1 == GPIODirection(pin, IN))
        {
		fprintf(stderr, "[Input] Error for pin %d\n", pin);
                exit(-1);
        }
}

/*
 * Set GPIO directions
 */
void set_output(int pin)
{
	if (-1 == GPIODirection(pin, OUT))
        {
		fprintf(stderr, "[Output] Error for pin %d\n", pin);
                exit(-1);
        }
}

/*
 * Disable GPIO pins
 */
void disable_pin(int pin)
{
	if (-1 == GPIOUnexport(pin))
        {
		fprintf(stderr, "[Disable] Error for pin %d\n", pin);
                exit(-1);
        }
}

/*
 * Write GPIO value
 * hmmm, should out be bool or int type?
 * I just don't want to hold up so much space for this variable
 * 
 * How do I set hex values to a char to write to pinS
 * I want to treat it like a port
 */
void gpio_output(int pin, int out)
{
        if (-1 == GPIOWrite(pin, out))
        {
		fprintf(stderr, "[Write output] Error for pin %d\n", pin);
                exit(-1);
        }
}


// Recall 0x00 is 8 bits long, one byte
// Which is the size for a char
// To turn on an Rpi, just set to one
unsigned char RPIPORT = 0x00;

/* Takes port variable and parse it to write to output
 * Note that we are only using the right most bits of RPIPORT
 * To do this, maybe I can utilize ia shift
 * https://www.geeksforgeeks.org/multithreading-c-2/
 * Must incorporate threading in this 
 */
void Set_Port()
{
        RPIPORT &= 0x0F; // Only worry about the right most pins

        // Get the pin values from the port variable
        // anding it with 0x01 just incase there are bit stragglers on the left most bits 
        // I need to create a static pwm here 
        gpio_output(GPIO06NUM,((RPIPORT >> GPIO06) & 0x01));
        gpio_output(GPIO13NUM,((RPIPORT >> GPIO13) & 0x01));
        gpio_output(GPIO19NUM,((RPIPORT >> GPIO19) & 0x01));
        gpio_output(GPIO26NUM,((RPIPORT >> GPIO26) & 0x01));
}
