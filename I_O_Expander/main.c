/*
 * main.c
 *
 *  Created on: May 8, 2019
 *      Author: dev1
 */


#include <avr/io.h>
#include <util/delay.h>
#include "pca9554.h"

#define PCA9554_1_ADDRESS                 0x40
#define PCA9554_2_ADDRESS                 0x42


uint8_t data = 0;

int main()
{
	Pca9554_Init(PCA9554_1_ADDRESS);
	// Set pin mode of pin 0 to output
	Pca9554_pinMode(PCA9554_1_ADDRESS, 0, 1);
	Pca9554_pinMode(PCA9554_1_ADDRESS, 7, 0);

	// Make it low
	Pca9554_digitalWrite(PCA9554_1_ADDRESS, 0, 1);

	Pca9554_Init(PCA9554_2_ADDRESS);
	// Set pin mode of pin 0 to output
	Pca9554_pinMode(PCA9554_2_ADDRESS, 0, 1);

	// Make it low
	Pca9554_digitalWrite(PCA9554_2_ADDRESS, 0, 1);
	while(1)
	{
		/*
		// Make pin 0 high for a while
		Pca9554_digitalWrite(PCA9554_1_ADDRESS, 0, 1);
		//_delay_ms(1);
		Pca9554_digitalWrite(PCA9554_2_ADDRESS, 0, 0);
		_delay_ms(500);

		// And bring it low again
		Pca9554_digitalWrite(PCA9554_1_ADDRESS, 0, 0);
		//_delay_ms(1);
		Pca9554_digitalWrite(PCA9554_2_ADDRESS, 0, 1);
		*/
		_delay_ms(100);
		if(Pca9554_digitalRead(PCA9554_1_ADDRESS, 7))
			Pca9554_digitalWrite(PCA9554_1_ADDRESS, 0, 0);
		else
			Pca9554_digitalWrite(PCA9554_1_ADDRESS, 0, 1);

	}
	return 0;
}
