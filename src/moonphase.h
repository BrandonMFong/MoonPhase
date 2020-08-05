/*
 * Is this sending serial data?
 * Use the gpio numbers
 */

#include "RPi_GPIO_Code_Samples.h"

/*
 * Enable GPIO pins
 */
void init_gpio(int pin)
{
	if (-1 == GPIOExport(pin)) 
        exit(-1);
}

/*
 * Set GPIO directions
 */
void set_input(int pin)
{
	if (-1 == GPIODirection(pin, IN))
        exit(-1);
}

/*
 * Set GPIO directions
 */
void set_output(int pin)
{
	if (-1 == GPIODirection(pin, OUT))
        exit(-1);
}

/*
 * Disable GPIO pins
 */
void disable_pin()
{
	if (-1 == GPIOUnexport(POUT) || -1 == GPIOUnexport(PIN))
        exit(-1);
}

/*
 * Write GPIO value
 * hmmm, should out be bool or int type?
 * I just don't want to hold up so much space for this variable
 */
void gpio_output(int pin, bool out)
{
    if (-1 == GPIOWrite(POUT, (int)out))
        exit(-1);
}


// int main(int argc, char *argv[])
// {
//     // Put the array indexes in an array 
//     int[4]pins = 1,2,3,4;

// 	return(0);
// }
