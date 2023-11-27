/**
 * Kap18-SPI-7-Segment-Display
 * ===========================
 *
 * Ansteuerung einer 7-Segment-Anzeige mit dem MAX7219 ueber SPI.
 */

#include <stm32f4xx.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Kommentar in Zeile 15 entfernen, wenn Sie die MCAL testen möchten.
 */
#define MCAL

/**
 * Kommentar einfuegen fuer SPI-16-Bit-Datenformat
 */
#define SPI_DATAFORMAT_8Bit


#include <mcalSysTick.h>
#include <mcalGPIO.h>
#include <mcalSPI.h>
#include <max7219.h>

void max7219Init(SPI_TypeDef *spi);

bool timerTrigger = false;


int main(void)
{
    GPIO_TypeDef *port = GPIOA;
    SPI_TypeDef  *spi  = SPI1;
    uint32_t      spiTimer = 0UL;
    uint32_t      data = 1234UL;
    uint8_t       d0, d1, d2, d3, d4, d5, d6, d7;



    // Initialisiert den Systick-Timer
    systickInit(SYSTICK_1MS);
    systickSetMillis(&spiTimer, 1);

    // SPI: Wir verwenden GPIOA
    gpioInitPort(port);
    gpioSelectPinMode(port, MAX7219_CS, OUTPUT);        // PA8 = ~CS
    gpioSelectPushPullMode(port, MAX7219_CS, PULLUP);
    gpioSelectPinMode(port, MAX7219_CLK, ALTFUNC);      // PA5 = SPI1 Clock
    gpioSelectAltFunc(port, MAX7219_CLK, AF5);
    gpioSelectPinMode(port, MAX7219_MOSI, ALTFUNC);     // PA7 = SPI1 MOSI
    gpioSelectAltFunc(port, MAX7219_MOSI, AF5);

    // Init SPI1
    spiSelectSPI(spi);

    spiInitSPI(spi, CLK_DIV_16, DATA_FORMAT_8, SSM_ON, SSI_LVL_HIGH, MASTER, SPI_PHASE_EDGE_1, SPI_IDLE_LOW);



    // Init MAX7219
    max7219Init(spi);
    max7219SetDecodeMode(spi, DECODE_ALL);
    max7219ResetDigits(spi, 0);

//    max7219Shutdown(spi);
    max7219TurnOn(spi);

    while (1)
    {
        if (timerTrigger == true)
        {
            DECREMENT_TIMER(spiTimer);
            timerTrigger = false;
        }

        if (isSystickExpired(spiTimer))
        {
            systickSetMillis(&spiTimer, 1);

            // Berechnung der einzelnen Stellen der Ziffern
            d0 = data % 10;
            d1 = (data / 10) % 10;
            d2 = (data / 100)  % 10;
            d3 = (data / 1000) % 10;
            d4 = (data / 10000) % 10;
            d5 = (data / 100000) % 10;
            d6 = (data / 1000000) % 10;
            d7 = (data / 10000000) % 10;

            // Prueft das gewaehlte Datenformat
            if (!(spi->CR1 & SPI_CR1_DFF))
            {
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DIG0);
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, d0);

                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DIG1);
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, d1);

                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DIG2);
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, d2);

                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DIG3);
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, d3);

                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DIG4);
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, d4);

                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DIG5);
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, d5);

                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DIG6);
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, d6);

                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, REG_DIG7);
                spiWriteByte(spi, MAX7219_CS_PORT, MAX7219_CS, d7);
            }
            else
            {
                spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (REG_DIG0_SL8 | d0));
                spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (REG_DIG1_SL8 | d1));
                spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (REG_DIG2_SL8 | d2));
                spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (REG_DIG3_SL8 | d3));
                spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (REG_DIG4_SL8 | d4));
                spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (REG_DIG5_SL8 | d5));
                spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (REG_DIG6_SL8 | d6));
                spiWriteWord(spi, MAX7219_CS_PORT, MAX7219_CS, (REG_DIG7_SL8 | d7));
            }

            if (++data > 99999999)
            {
                data = 0;
            }
        }
    }

    return 0;
}


