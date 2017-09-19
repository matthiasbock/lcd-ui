/**
 * Arduino-compatible SPI library
 * for STM32F4xx MCUs
 */

#ifndef DSPI_H
#define DSPI_H

#include <stm32f4xx.h>
#include <stdbool.h>

class DSPI
{
    bool initialized = false;
    SPI_HandleTypeDef* spi;

  public:
    /**
     * Initialize SPI periperhal
     * using the settings provided via the parameter
     */
    DSPI(SPI_HandleTypeDef* spi);

    void begin();
    void setSpeed(uint32_t baud);
    void setTransferSize(uint8_t bits);
    uint32_t transfer(uint32_t out);
};

#endif // DSPI_H
