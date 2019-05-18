/*
 * main.c
 *
 *  Created on: May 18, 2019
 *      Author: dev1
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spi.h"

volatile uint8_t OVFs = 0, flag = 0;

void reverse(int a[], int sz);
void rotate(int array[], int size, int amt);


int main()
{
	SPI_Init();
	DDRA = 0xFF;
	PORTB |= (1 << 3);
	PORTB |= (1 << 4);
	PORTA = 0xFF;

	TCCR2 |= ((1 << CS22) | (1 << CS21) | (1 << CS20));

	TIMSK |= (1 << TOIE2);
	sei();

	uint16_t i;
	int x = 0;

	uint8_t arr[] = {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x26, 0x23, 0x21, 0x23, 0x26, 0xfc
	};


	while(1)
	{
			for(i=0x8000;i>0;i/=2)
			{
				PORTA = ~arr[x];
				PORTB &= ~(1 << 4);
				SPI_Write_u16(i);
				PORTB |= (1 << 4);
				_delay_ms(10);
				if(x == 15)
					x = 0;
				else
					x++;
			}
/*
		if(flag == 1)
		{
			rotate(arr, 8, -1);
			flag = 0;
		}
		*/
	}

	return 0;
}

ISR(TIMER2_OVF_vect)
{
	if(OVFs < 60)
	{
		OVFs++;
	}
	else
	{
		OVFs = 0;
		flag = 1;
	}
}

void reverse(int a[], int sz) {
  int i, j;
  for (i = 0, j = sz; i < j; i++, j--) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }
}

void rotate(int array[], int size, int amt) {
  if (amt < 0)
    amt = size + amt;
  reverse(array, size-amt-1);
  reverse(array+size-amt, amt-1);
  reverse(array, size-1);
}
