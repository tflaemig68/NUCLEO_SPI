/**
 * max7219.h
 *
 *  Created on: 17.10.2020
 *      Author: Ralf Jesse
 *       Email: embedded@ralf-jesse.de
 */

#ifndef MAX7219_H_
#define MAX7219_H_

#include <stm32f4xx.h>

#define MAX7219_CS_PORT     (GPIOA)
#define MAX7219_CS          (PIN8)
#define MAX7219_MOSI        (PIN7)
#define MAX7219_CLK         (PIN5)

typedef enum
{
    // Use this when using 8-bit transfer
    REG_NOOP        =  0,
    REG_DIG0,
    REG_DIG1,
    REG_DIG2,
    REG_DIG3,
    REG_DIG4,
    REG_DIG5,
    REG_DIG6,
    REG_DIG7,
    REG_DECODE,
    REG_INTENSITY,
    REG_SCAN_LIMIT,
    REG_SHUTDOWN,
    REG_DISPTEST    = 15,

    // Use this when using 16-bit transfer
    // Addresses are then left-shifted by 8
    REG_NOOP_SL8        =  (0 << 8),
    REG_DIG0_SL8        =  (1 << 8),
    REG_DIG1_SL8        =  (2 << 8),
    REG_DIG2_SL8        =  (3 << 8),
    REG_DIG3_SL8        =  (4 << 8),
    REG_DIG4_SL8        =  (5 << 8),
    REG_DIG5_SL8        =  (6 << 8),
    REG_DIG6_SL8        =  (7 << 8),
    REG_DIG7_SL8        =  (8 << 8),
    REG_DECODE_SL8      =  (9 << 8),
    REG_INTENS_SL8      = (10 << 8),
    REG_SCAN_LIMIT_SL8  = (11 << 8),
    REG_SHUTDOWN_SL8    = (12 << 8),
    REG_DISPTEST_SL8    = (15 << 8)

} MAX7219_REG_t;

typedef enum
{
    INT_MIN         = 0,
    INT_1,
    INT_2,
    INT_3,
    INT_4,
    INT_5,
    INT_6,
    INT_7,
    INT_8,
    INT_9,
    INT_10,
    INT_11,
    INT_12,
    INT_13,
    INT_14,
    INT_MAX
} MAX7219_INTENSITY_t;

typedef enum
{
    TEST_OFF        = 0,
    TEST_ON
} MAX7219_TESTMODE_t;

typedef enum
{
    SHUTDOWN = 0,
    NORMAL_OP
} MAX7219_OPMODE_t;

typedef enum
{
    NO_DECODE           = 0,
    DECODE_DIG0         = 1,
    DECODE_DIG0_TO_DIG3 = 0x0F,
    DECODE_ALL          = 0xFF
} MAX7219_DECODE_t;

//extern void max7219Init(SPI_TypeDef *spi);
extern void max7219Test(SPI_TypeDef *spi, MAX7219_TESTMODE_t testMode);
extern void max7219Shutdown(SPI_TypeDef *spi);
extern void max7219TurnOn(SPI_TypeDef *spi);
extern void max7219SetDecodeMode(SPI_TypeDef *spi, MAX7219_DECODE_t mode);
extern void max7219TestDigits(SPI_TypeDef *spi, uint8_t value);
extern void max7219ResetDigits(SPI_TypeDef *spi, uint8_t value);
extern void max7219Clear(SPI_TypeDef *spi);

#endif /* MAX7219_H_ */
