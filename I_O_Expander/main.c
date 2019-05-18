/*
 * main.c
 *
 *  Created on: May 8, 2019
 *      Author: dev1
 */


#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pca9554.h"
#include "char_lcd.h"

#define PCA9554_1_ADDRESS                 0x40
#define PCA9554_2_ADDRESS                 0x42
#define PCA9554_3_ADDRESS                 0x46

#define NORMAL	0
#define ABNORMAL	1

typedef enum{RUN, ALARM} state_t;

state_t mcu_state = RUN;

uint8_t data = 0;
volatile uint8_t i;
uint8_t arr[2];

uint8_t inp[8] = {NORMAL, NORMAL, NORMAL, NORMAL, NORMAL, NORMAL, NORMAL, NORMAL};

void init_INT0(void);

int main()
{
	LCD_init();

	Pca9554_Init(PCA9554_1_ADDRESS);
	// Set pin mode of pin [0-7] to output
	for(i=0;i<8;++i)
		Pca9554_pinMode(PCA9554_1_ADDRESS, i, OUTPUT);

	Pca9554_Init(PCA9554_3_ADDRESS);
	// Set pin mode of pin [0-7] to output
	for(i=0;i<8;++i)
		Pca9554_pinMode(PCA9554_3_ADDRESS, i, OUTPUT);

	Pca9554_Init(PCA9554_2_ADDRESS);
	// Set pin mode of pin [0-7] to input
	for(i=0;i<8;++i)
			Pca9554_pinMode(PCA9554_2_ADDRESS, i, INPUT);

	init_INT0();
	sei();

	while(1)
	{
		switch(mcu_state)
		{
		case RUN:
			LCD_goto_xy(0,0);
			LCD_send_string("Device in service");
			break;
		case ALARM:
			LCD_goto_xy(0,1);
			LCD_send_string("Alarm");
			LCD_goto_xy(0,0);
			for(i=0;i<8;++i)
			{
				if(inp[i] == ABNORMAL)
				{
					LCD_send_string("input : ");
					itoa((i+1), arr, 10);
					LCD_send_string(arr);
				}
			}
			break;
		}
	}
	return 0;
}

ISR(INT0_vect)
{
	for(i=0;i<8;++i)
	{
		if(Pca9554_digitalRead(PCA9554_2_ADDRESS, i))
		{
			mcu_state = ALARM;
			inp[i] = ABNORMAL;
			LCD_clear();
			Pca9554_digitalWrite(PCA9554_1_ADDRESS, i, HIGH);
			Pca9554_digitalWrite(PCA9554_3_ADDRESS, i, HIGH);
		}
		else
		{
			Pca9554_digitalWrite(PCA9554_1_ADDRESS, i, LOW);
			Pca9554_digitalWrite(PCA9554_3_ADDRESS, i, LOW);
		}
	}
}

void init_INT0(void)
{
	MCUCR |= (1 << ISC01); // falling edge
	MCUCR &= ~(1 << ISC00);
	GICR |= (1 << INT0);
}
