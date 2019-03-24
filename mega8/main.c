/*
 * main.c
 *
 *  Created on: Mar 5, 2019
 *      Author: dev1
 */

//#define F_CPU 8000000UL

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "pwm.h"

int main(){

	pwm2_Init(PHASE_CORRECT_PWM);
	pwm2_Set_Duty(50);
	pwm2_Start();

	while(1){

	}
	return 0;
}
