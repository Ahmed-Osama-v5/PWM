/*
 * pca9554.h
 *
 *  Created on: May 8, 2019
 *      Author: dev1
 */

#ifndef PCA9554_H_
#define PCA9554_H_

#define NORMAL                          0
#define INVERTED                        1

void Pca9554_Init(uint8_t address);
static void writeRegister(uint8_t i2cAddress, uint8_t reg, uint8_t value);
static uint16_t readRegister(uint8_t i2cAddress, uint8_t reg);
uint8_t Pca9554_pinMode(uint8_t address, uint8_t pin, uint8_t mode);
uint8_t Pca9554_pinPolarity(uint8_t address, uint8_t pin, uint8_t polarity);
uint8_t Pca9554_digitalWrite(uint8_t address, uint8_t pin, uint8_t val);
uint8_t Pca9554_digitalRead(uint8_t address, uint8_t pin);


uint8_t m_inp;
uint8_t m_out;
uint8_t m_pol;
uint8_t m_ctrl;

#endif /* PCA9554_H_ */
