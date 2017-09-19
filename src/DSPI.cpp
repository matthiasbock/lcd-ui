
#include <DSPI.h>


DSPI::DSPI(SPI_HandleTypeDef* spi)
:spi(spi)
{
    initialized = false;

    __HAL_RCC_SPI1_CLK_ENABLE();

    if (HAL_SPI_Init(spi) != HAL_OK)
        return;

    HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);

    __HAL_SPI_ENABLE(spi);

    initialized = true;
}
