#include "spiPrivate.h"

void SpiUnblockTask(Spi_t *pSpi)
{
    BaseType_t  xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(pSpi->semaphoreHoldTask, &xHigherPriorityTaskWoken);

    if(xHigherPriorityTaskWoken != pdFALSE)
    {
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
}


void SpiDmaTxIrqHandler(Spi_t *pSpi)
{ 
    SpiUnblockTask(pSpi);
}
void SpiDmaRxIrqHandler(Spi_t *pSpi)
{ 
    SpiUnblockTask(pSpi);
}
void SpiIrqHandler(Spi_t *pSpi)
{ 
    if ((pSpi->pSpiHard->SR && SPI_SR_OVR)  || 
        (pSpi->pSpiHard->SR && SPI_SR_MODF) || 
        (pSpi->pSpiHard->SR && SPI_SR_UDR)  )
    {
        pSpi->state = SPI_STATE_HARD_ERROR;
        pSpi->pSpiHard->SR &= (~SPI_SR_OVR) & (~SPI_SR_MODF) & (~SPI_SR_UDR);
        pSpi->pSpiHard->DR;
        pSpi->pSpiHard->CR &= ~DMA_SxCR_EN;
        pSpi->pSpiHard->CR &= ~DMA_SxCR_EN;

        SpiUnblockTask(pSpi);
    }

    if (pSpi->pSpiHard->SR && SPI_SR_RXNE)
    {
        SpiUnblockTask(pSpi);
    }
}