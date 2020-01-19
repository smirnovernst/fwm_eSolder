#include "stm32f4xx.h"
#include "spiPrivate.h"



SpiStatus_t SpiTxRxDma(Spi_t *pSpi,uint8_t *pSrc, uint8_t *pDst, uint8_t len, uint16_t timeout_ms)
{
    if ((NULL == pSpi) || (NULL == pSrc) || (NULL == pDst))
    {
        return SPI_STATUS_INVALID_PARAM;
    }
    if (xSemaphoreTake(pSpi->semaphoreBusy, timeout_ms / portTICK_PERIOD_MS) != pdTRUE) 
    {
        return SPI_STATUS_TIMEOUT;
    }

    SPI_RXDMA_IRQ_ENABLE(pSpi);

    pSpi->pDmaStreamRx->CR &= ~DMA_SxCR_EN;
    pSpi->pDmaStreamRx->M0AR = (uint32_t)pDst;
    pSpi->pDmaStreamRx->NDTR = len;
    pSpi->pDmaStreamRx->CR |= DMA_SxCR_EN;

    pSpi->pDmaStreamTx->CR &= ~DMA_SxCR_EN;
    pSpi->pDmaStreamTx->M0AR = (uint32_t)pSrc;
    pSpi->pDmaStreamTx->NDTR = len;
    pSpi->pDmaStreamTx->CR |= DMA_SxCR_EN;

    if (xSemaphoreTake(pSpi->semaphoreHoldTask, timeout_ms / portTICK_PERIOD_MS) != pdTRUE) 
    {
        SPI_RXDMA_IRQ_DISABLE(pSpiHard);
        xSemaphoreGive(pSpi->semaphoreBusy);
        return SPI_STATUS_TIMEOUT;
    }
    SPI_RXDMA_IRQ_DISABLE(pSpiHard);
    xSemaphoreGive(pSpi->semaphoreBusy);
    return SPI_STATUS_OK;
}
SpiStatus_t SpiTxDma(Spi_t *pSpi, uint8_t *pSrc, uint8_t len,  uint16_t timeout_ms)
{
    if ((NULL == pSpi) || (NULL == pSrc))
    {
        return SPI_STATUS_INVALID_PARAM;
    }
    if (xSemaphoreTake(pSpi->semaphoreBusy, timeout_ms / portTICK_PERIOD_MS) != pdTRUE) 
    {
        return SPI_STATUS_TIMEOUT;
    }

    SPI_TXDMA_IRQ_ENABLE(pSpi);

    pSpi->pDmaStreamTx->CR &= ~DMA_SxCR_EN;
    pSpi->pDmaStreamTx->M0AR = (uint32_t)pSrc;
    pSpi->pDmaStreamTx->NDTR = len;
    pSpi->pDmaStreamTx->CR |= DMA_SxCR_EN;

    if (xSemaphoreTake(pSpi->semaphoreHoldTask, timeout_ms / portTICK_PERIOD_MS) != pdTRUE) 
    {
        SPI_TXDMA_IRQ_DISABLE(pSpi);
        xSemaphoreGive(pSpi->semaphoreBusy);
        return SPI_STATUS_TIMEOUT;
    }
    SPI_TXDMA_IRQ_DISABLE(pSpi);
    xSemaphoreGive(pSpi->semaphoreBusy);
    return SPI_STATUS_OK;
}

SpiStatus_t SpiTxByte(Spi_t *pSpi, uint8_t byte, uint16_t timeout_ms)
{
    if (NULL == pSpi) 
    {
        return SPI_STATUS_INVALID_PARAM;
    }
    if (xSemaphoreTake(pSpi->semaphoreBusy, timeout_ms / portTICK_PERIOD_MS) != pdTRUE) {
        return SPI_STATUS_TIMEOUT;
    }

    TickType_t xTicksToWait = timeout_ms;
    TimeOut_t xTimeOut;
    while (pSpi->pSpiHard->SR && !SPI_SR_TXE) 
    {
        if (xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) != pdFALSE)
        {
            xSemaphoreGive(pSpi->semaphoreBusy);
            return SPI_STATUS_TIMEOUT;
        }
    }

    pSpi->pSpiHard->DR = byte;
    xSemaphoreGive(pSpi->semaphoreBusy);
    return SPI_STATUS_OK;
}



SpiStatus_t SpiTxRxByte(Spi_t *pSpi, uint8_t sendByte, uint8_t *pReceiveByte, uint16_t timeout_ms)
{
    if ((NULL == pSpi)||(NULL == pReceiveByte)) 
    {
        return SPI_STATUS_INVALID_PARAM;
    }
    if (xSemaphoreTake(pSpi->semaphoreBusy, timeout_ms / portTICK_PERIOD_MS) != pdTRUE) 
    {
        return SPI_STATUS_TIMEOUT;
    }

    TickType_t xTicksToWait = timeout_ms;
    TimeOut_t xTimeOut;
    while (pSpi->pSpiHard->SR && !SPI_SR_TXE) 
    {
        if (xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) != pdFALSE)
        {
            xSemaphoreGive(pSpi->semaphoreBusy);
            return SPI_STATUS_TIMEOUT;
        }
    }
    SPI_RXNE_IRQ_ENABLE(pSpi);
    
    pSpi->pSpiHard->DR; //Dummy read for clear probably IRQ RXNE flag
    pSpi->pSpiHard->SR = 0;
    pSpi->pSpiHard->DR = sendByte;


    if (xSemaphoreTake(pSpi->semaphoreHoldTask, timeout_ms / portTICK_PERIOD_MS) != pdTRUE) 
    {
        SPI_RXNE_IRQ_DISABLE(pSpi->pSpiHard);
        xSemaphoreGive(pSpi->semaphoreBusy);
        return SPI_STATUS_TIMEOUT;
    }

    SPI_RXNE_IRQ_DISABLE(pSpi);
    *pReceiveByte = pSpi->pSpiHard->DR;
    xSemaphoreGive(pSpi->semaphoreBusy);
    return SPI_STATUS_OK;
}