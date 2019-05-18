/*
 * spi.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

/*********************************
 * Title  : SPI.
 * Author : Ahmed Osama.
 * Date   : 03 Oct 2015.
 * Contact: engahmed2015@gmail.com
 *********************************/
#include <avr/io.h>
#include <stdint.h>
#include "spi.h"

void SPI_Init()
{
    SPSR |= (1 << SPI2X);
    SPCR = ((1 << SPE) | (1 << MSTR) | (1 << SPR1));  // Enable SPI Master mode @ 500 KHz.
    DDRB |= ((1 << MOSI) | (1 << SCK) | (1 << 4) | (1 << 3));   // Setting MOSI and SCK as digital outputs.
}

void SPI_Write_To_Address(uint8_t addr, uint8_t data)
{
    SPDR = addr;
    while(! (SPSR & (1 << SPIF)));

    SPDR = data;
    while(! (SPSR & (1 << SPIF)));
}

void SPI_Write(uint8_t data)
{
    SPDR = data;
    while(! (SPSR & (1 << SPIF)));
}

void SPI_Write_u16(uint16_t data)
{
    SPDR = data >> 8;
    while(! (SPSR & (1 << SPIF)));
    SPDR = data;
    while(! (SPSR & (1 << SPIF)));
}

uint8_t SPI_Read(uint8_t addr)
{
    while(! (SPSR & (1 << SPIF)));
    return SPDR;
}

