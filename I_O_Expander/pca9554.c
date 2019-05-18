/*
 * pca9554.c
 *
 *  Created on: May 8, 2019
 *      Author: dev1
 */
#include <avr/io.h>
#include "pca9554.h"
#include "i2c.h"

#define PCA9554_REG_INP                 0
#define PCA9554_REG_OUT                 1
#define PCA9554_REG_POL                 2
#define PCA9554_REG_CTRL                3

uint8_t pinNum2bitNum[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

/***************************************************************************
 *
 *  Writes 8-bits to the specified destination register
 *
 **************************************************************************/
void writeRegister(uint8_t i2cAddress, uint8_t reg, uint8_t value)
{
  I2C_Send_start();
  I2C_Send_Address(i2cAddress);
  I2C_Send_data((uint8_t)reg);
  I2C_Send_data((uint8_t)value);
  I2C_Stop();
}

/***************************************************************************
 *
 * Reads 8-bits from the specified source register
 *
 **************************************************************************/
uint16_t readRegister(uint8_t i2cAddress, uint8_t reg)
{
  I2C_Send_start();
  I2C_Send_Address(i2cAddress);
  I2C_Send_data(reg);
  I2C_Send_Repeated_start();
  i2cAddress |= (1 << 0);
  I2C_Send_Address(i2cAddress);
  uint16_t data = I2C_Receive_Data();
  I2C_Stop();
  return data;
}

/***************************************************************************
 *
 * Constructor for the Pca9554Class class, not much here yet
 *
 **************************************************************************/
//Pca9554Class::Pca9554Class(void) { }

/***************************************************************************
 *
 * Begin method. This method must be called before using this library
 * either directly if the class is initializing the Wire library or by
 * calling this library's function begin(sda, scl) in which case that
 * function will call this one.
 *
 **************************************************************************/
void Pca9554_Init(uint8_t address)
{
	I2C_Master_Init();
  // Read out default values from the registers to the shadow variables.
  m_inp = readRegister(address, PCA9554_REG_INP);
  m_out = readRegister(address, PCA9554_REG_OUT);
  m_pol = readRegister(address, PCA9554_REG_POL);
  m_ctrl = readRegister(address, PCA9554_REG_CTRL);
}

/***************************************************************************
 *
 * Sets the desired pin mode
 *
 **************************************************************************/
uint8_t Pca9554_pinMode(uint8_t address, uint8_t pin, uint8_t mode)
{
  // Make sure the pin number is OK
  if (pin >= sizeof pinNum2bitNum) {
    return 0;
  }

  // Calculate the new control register value
  if (mode == 1) {
    m_ctrl &= ~pinNum2bitNum[pin];
  } else if (mode == 0) {
    m_ctrl |= pinNum2bitNum[pin];
  } else {
    return 0;
  }

  writeRegister(address, PCA9554_REG_CTRL, m_ctrl);

  return 1;
}


/***************************************************************************
 *
 * Sets the desired pin polarity. This can be used to invert inverse
 * hardware logic.
 *
 **************************************************************************/
uint8_t Pca9554_pinPolarity(uint8_t address, uint8_t pin, uint8_t polarity)
{
  // Make sure pin number is OK
  if (pin >= sizeof pinNum2bitNum) {
    return 0;
  }

  if (polarity == INVERTED) {
    m_pol |= pinNum2bitNum[pin];
  } else if (polarity == NORMAL) {
    m_pol &= ~pinNum2bitNum[pin];
  } else {
    return 0;
  }

  writeRegister(address, PCA9554_REG_POL, m_pol);

  return 1;
}

/***************************************************************************
 *
 * Write digital value to pin
 *
 **************************************************************************/
uint8_t Pca9554_digitalWrite(uint8_t address, uint8_t pin, uint8_t val)
{
  // Make sure pin number is OK
  if (pin >= sizeof pinNum2bitNum) {
    return 0;
  }

  if (val == 1) {
    m_out |= pinNum2bitNum[pin];
  } else {
    m_out &= ~pinNum2bitNum[pin];
  }

  writeRegister(address, PCA9554_REG_OUT, m_out);
  return 1;
}

/***************************************************************************
 *
 * Read digital value from pin.
 * Note, so far this function will fail silently if the pin parameter is
 * incorrectly specified.
 *
 **************************************************************************/
uint8_t Pca9554_digitalRead(uint8_t address, uint8_t pin)
{
  return ((readRegister(address, PCA9554_REG_INP) & pinNum2bitNum[pin]) != 0);
}

