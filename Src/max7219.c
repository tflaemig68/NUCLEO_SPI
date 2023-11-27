/**
 * max7219.c
 *
 *  Created on: 17.10.2020
 *      Author: Ralf Jesse
 *       Email: embedded@ralf-jesse.de
 */

#include <max7219.h>
#include <mcalSysTick.h>
#include <mcalGPIO.h>
#include <mcalSPI.h>

void max7219Init(SPI_TypeDef *spi)
{
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DECODE);
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, 0);

    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_INTENSITY);
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, 3);

    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_SCAN_LIMIT);
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, 7);

    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_SHUTDOWN);
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, NORMAL_OP);

    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DISPTEST);
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, TEST_OFF);
}

void max7219TurnOn(SPI_TypeDef *spi)
{
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_SHUTDOWN);
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, 1);
}

void max7219Shutdown(SPI_TypeDef *spi)
{
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_SHUTDOWN);
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, 0);
}

void max7219SetDecodeMode(SPI_TypeDef *spi, MAX7219_DECODE_t mode)
{
    uint8_t decodeMode = mode;

    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DECODE);
    spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, decodeMode);
}

void max7219ResetDigits(SPI_TypeDef *spi, uint8_t value)
{
    uint8_t reg = REG_DIG0;

    for (reg = REG_DIG0; reg < REG_DECODE; reg++)
    {
        spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, reg);
        spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, value);
    }
}

void max7219Clear(SPI_TypeDef *spi)
{
    uint16_t reg;

    for (reg = REG_DIG0_SL8; reg < REG_DECODE_SL8; reg++)
    {
        spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (reg | 0x0F) & 0x0F);
    }
}

void max7219TestDigits(SPI_TypeDef *spi, uint8_t value)
{
    uint8_t reg = 0;

    for (reg = REG_DIG0; reg < REG_DECODE; reg++)
    {
        spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, reg);
        spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, value);
    }
}
