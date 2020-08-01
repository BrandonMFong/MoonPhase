#include "moonphase.h"

int
main(int argc, char *argv[])
{
	int repeat = 10;

	/*
	 * Enable GPIO pins
	 */
	if (-1 == GPIOExport(POUT) || -1 == GPIOExport(PIN))
		return(1);

	/*
	 * Set GPIO directions
	 */
	if (-1 == GPIODirection(POUT, OUT) || -1 == GPIODirection(PIN, IN))
		return(2);

	do {
		/*
		 * Write GPIO value
		 */
		if (-1 == GPIOWrite(POUT, repeat % 2))
			return(3);

		/*
		 * Read GPIO value
		 */
		printf("I'm reading %d in GPIO %d\n", GPIORead(PIN), PIN);

		usleep(500 * 1000);
	}
	while (repeat--);

	/*
	 * Disable GPIO pins
	 */
	if (-1 == GPIOUnexport(POUT) || -1 == GPIOUnexport(PIN))
		return(4);

	return(0);
}
