#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

typedef enum 
{
    SPI_STATE_NOINIT = 0,
    SPI_STATE_IDLE,
    SPI_STATE_RUN,
    SPI_STATE_HARD_ERROR,
    SPI_STATE_INVALID_PARAM,
    SPI_STATE_NONE
}SpiState_t;

typedef struct Spi_t
{
    SPI_TypeDef         *pSpiHard;
    DMA_TypeDef         *pDmaTx;
    DMA_TypeDef         *pDmaRx;                             
    DMA_Stream_TypeDef	*pDmaStreamTx;
    DMA_Stream_TypeDef	*pDmaStreamRx;
    uint8_t		        dmaChannelRx	:4;
    uint8_t		        dmaChannelTx	:4;
    SpiState_t          state;
    SemaphoreHandle_t   semaphoreBusy;
}Spi_t;

SpiState_t SpiTxRxDma(Spi_t *pSpi,uint8_t *pSrc, uint8_t *pDst, uint8_t len, uint16_t timeout_ms);
SpiState_t SpiTxDma(Spi_t *pSpi, uint8_t *pSrc, uint8_t len,  uint16_t timeout_ms);
SpiState_t SpiTxByte(Spi_t *pSpi, uint8_t byte, uint16_t timeout_ms);
SpiState_t SpiTxRxByte(Spi_t *pSpi, uint8_t sendByte, uint8_t *pReceiveByte, uint16_t timeout_ms);

#endif //!SPI_H_
