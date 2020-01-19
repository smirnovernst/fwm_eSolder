#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

typedef enum
{
    SPI_STATE_NO_INIT = 0, 
    SPI_STATE_OK,
    SPI_STATE_HARD_ERROR
}SpiState_t;

typedef enum 
{
    SPI_STATUS_OK = 0,
    SPI_STATUS_NOINIT,
    SPI_STATUS_HARD_ERROR,
    SPI_STATUS_INVALID_PARAM,
    SPI_STATUS_TIMEOUT,
    SPI_STATUS_BUSY,
    SPI_STATUS_NONE
}SpiStatus_t;

typedef struct Spi_t
{
    SPI_TypeDef         *pSpiHard;
    DMA_TypeDef         *pDmaTx;
    DMA_TypeDef         *pDmaRx;                             
    DMA_Stream_TypeDef	*pDmaStreamTx;
    DMA_Stream_TypeDef	*pDmaStreamRx;
    uint8_t		        dmaChannelTx	:4;
    uint8_t		        dmaChannelRx	:4;
    SemaphoreHandle_t   semaphoreBusy;
    SemaphoreHandle_t   semaphoreHoldTask;
    SpiState_t          state;
}Spi_t;

SpiStatus_t SpiTxRxDma(Spi_t *pSpi,uint8_t *pSrc, uint8_t *pDst, uint8_t len, uint16_t timeout_ms);
SpiStatus_t SpiTxDma(Spi_t *pSpi, uint8_t *pSrc, uint8_t len,  uint16_t timeout_ms);
SpiStatus_t SpiTxByte(Spi_t *pSpi, uint8_t byte, uint16_t timeout_ms);
SpiStatus_t SpiTxRxByte(Spi_t *pSpi, uint8_t sendByte, uint8_t *pReceiveByte, uint16_t timeout_ms);

#endif //!SPI_H_
