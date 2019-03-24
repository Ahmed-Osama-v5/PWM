/*
 * pwm.c
 *
 *  Created on: Mar 9, 2019
 *      Author: dev1
 */

#include <avr/io.h>
#include <inttypes.h>
#include "pwm.h"

/**
 * Name : pwm2_Init
 * Param : void
 * return : void
 * Description : set OC2 pin as output,
 * and configures timer2 in Phase-correct PWM mode
 */
void pwm2_Init(pwm_Mode_t mode)
{
	PWM2_DDR |= (1 << PWM2_PIN); // set OC2 pin as output
	switch(mode)
	{
	case PHASE_CORRECT_PWM:
		/* Phase-correct PWM, Non-inverting OC2 */
		TCCR2 |= ((1 << WGM20) | (1 << COM21));
		break;
	case FAST_PWM:
		/* Fast PWM, Non-inverting OC2 */
		TCCR2 |= ((1 << WGM21) | (1 << WGM20) | (1 << COM21));
		break;
	}

	/* wait until timer is configured */
	while(ASSR & (1 << TCR2UB));
}

/**
 * Name : pwm2_Start
 * Param : void
 * return : void
 * Description : start timer2 by assigning prescaler to non-Zero value
 */
void pwm2_Start(void)
{
	TCCR2 |= ((1 << CS22) | (1 << CS20)); // start timer2 with N = 128
}

/**
 * Name : pwm2_Stop
 * Param : void
 * return : void
 * Description : stops timer2 by assigning prescaler to 0
 */
void pwm2_Stop(void)
{
	TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); // stop timer2
}

/**
 * Name : pwm2_Set_Duty
 * Param : duty cycle in the range of 0-100
 * return : void
 * Description : updates the OCR2 register with the value of duty cycle
 */
void pwm2_Set_Duty(uint8_t duty)
{
	OCR2 = remap(0, 100, 0, 255, duty);
	/* wait until register is set with the new value */
	while(ASSR & (1 << OCR2UB));
}

/**
 * Name : remap
 * Param : start1 "start of the wanted range", end1 "end of the wanted range"
 * start2 "start of the original range", end2 "end of the original range"
 * value "the value to be converted"
 * return : U8 value after conversion
 * Description : multiplies the value by a factor that is the ratio between the two ranges
 */
uint8_t remap(uint8_t start1, uint8_t end1, uint8_t start2, uint8_t end2, uint8_t value)
{
	float factor = (((float)end2 - (float)start2) / ((float)end1 - (float)start1));
	return ((uint8_t)(value * factor));
}
