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

	pwm_Mode_t mode = FAST_PWM;

	pwm2_Init(mode);
	pwm2_Set_Duty(50);
	pwm2_Start();

	while(1){

	}
	return 0;
}
