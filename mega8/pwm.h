/*
 * pwm.h
 *
 *  Created on: Mar 9, 2019
 *      Author: dev1
 */

#ifndef PWM_H_
#define PWM_H_

#define PWM2_DDR	DDRB
#define PWM2_PORT	PORTB
#define PWM2_PIN	3

typedef enum{PHASE_CORRECT_PWM, FAST_PWM} pwm_Mode_t;

void pwm2_Init(pwm_Mode_t mode);
void pwm2_Start(void);
void pwm2_Stop(void);
void pwm2_Set_Duty(uint8_t duty);
uint8_t remap(uint8_t start1, uint8_t end1, uint8_t start2, uint8_t end2, uint8_t value);

#endif /* PWM_H_ */
