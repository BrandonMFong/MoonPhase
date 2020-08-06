/*
 * Is this sending serial data?
 * Use the gpio numbers
 */

#include "RPi_GPIO_Code_Samples.h"
#include <stdbool.h>

/*
 * Enable GPIO pins
 */
void init_gpio(int pin)
{
	if (-1 == GPIOExport(pin)) 
        {
		fprintf(stderr, "[Init] Error for pin %d\n", pin);
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
 */
void gpio_output(int pin, int out)
{
        if (-1 == GPIOWrite(pin, out))
        {
		fprintf(stderr, "[Write output] Error for pin %d\n", pin);
                exit(-1);
        }
}
