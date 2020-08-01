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
		return(4);
}


int main(int argc, char *argv[])
{
	int repeat = 10;


	do {
		/*
		 * Write GPIO value
		 */
		if (-1 == GPIOWrite(POUT, repeat % 2))
			return(3);


		usleep(500 * 1000);
	}
	while (repeat--);

	return(0);
}
