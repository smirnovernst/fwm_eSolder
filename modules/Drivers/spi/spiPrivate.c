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
        pSpi->pDmaStreamRx->CR &= ~DMA_SxCR_EN;
        pSpi->pDmaStreamTx->CR &= ~DMA_SxCR_EN;
        
        SPI_RXNE_IRQ_DISABLE(pSpi);
        SPI_RXDMA_IRQ_DISABLE(pSpi);
        SPI_TXDMA_IRQ_DISABLE(pSpi);
        
        SpiUnblockTask(pSpi);
    }

    if (pSpi->pSpiHard->SR && SPI_SR_RXNE)
    {
        SpiUnblockTask(pSpi);
    }
}