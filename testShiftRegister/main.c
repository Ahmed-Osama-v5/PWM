/*
 * main.c
 *
 *  Created on: May 18, 2019
 *      Author: dev1
 */

#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

int main()
{
	SPI_Init();
	DDRA = 0xFF;
	PORTB |= (1 << 3);
	PORTB |= (1 << 4);
	PORTA = 0xFF;
	uint16_t i;
	int x;
	while(1)
	{
		for(x=7;x>=0;--x)
		{
			PORTA &= ~(1 << x);
			for(i=1;i<0x8000;i*=2)
			{
				PORTB &= ~(1 << 4);
				SPI_Write_u16(i);
				PORTB |= (1 << 4);
				_delay_ms(50);
			}
			PORTB &= ~(1 << 4);
			SPI_Write_u16(0x8000);
			PORTB |= (1 << 4);
			_delay_ms(50);
			PORTA = 0xFF;
		}
	}

	return 0;
}

