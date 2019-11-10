/*
*@File          spi_f4.h
*@Author        Ernst
*@Version       
*@Date          22.08.2018
*@Breif         
*/
#ifndef  SPIF4_H_
#define  SPIF4_H_
/*!****************************************************************************
* Include
*/
#include "stm32f4xx.h"

//FreeRTOS files 
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/*!****************************************************************************
* User define
*/

//============== SPI 1 ==============//
#define SPI1_USE                (1)
#define SPI1_DUPLEX             (1)
#define SPI1_InterruptPrior     (15)
#define SPI1_DmaInterruptPrior  (15)
#define SPI1_CPOL               (1)
#define SPI1_CPHA               (1)
#define SPI1_BR                 (SPI_CR1_BR_2)
#define SPI1_DMA_USE            (1)

#define SPI1_DMA_TX             (DMA2)
#define SPI1_DMA_STREAM_TX      (DMA2_Stream3)
#define SPI1_DMA_STREAM_TX_IRQ  (DMA2_Stream3_IRQn)
#define SPI1_DMA_STREAM_TX_IRQ_HANDLER DMA2_Stream3_IRQHandler
#define SPI1_DMA_CHANNEL_TX     (3)
#define SPI1_DMA_CLR_IRQ_TX()   (DMA2->LIFCR |= DMA_LIFCR_CTCIF3)

#define SPI1_DMA_RX             (DMA2)
#define SPI1_DMA_STREAM_RX      (DMA2_Stream0)
#define SPI1_DMA_STREAM_RX_IRQ  (DMA2_Stream0_IRQn)
#define SPI1_DMA_STREAM_RX_IRQ_HANDLER DMA2_Stream0_IRQHandler
#define SPI1_DMA_CHANNEL_RX     (3)
#define SPI1_DMA_CLR_IRQ_RX()   (DMA2->LIFCR |= DMA_LIFCR_CTCIF0)

//============== SPI 5 ==============//
#define SPI5_USE                (1)
#define SPI5_DUPLEX             (1)
#define SPI5_InterruptPrior     (15)
#define SPI5_DmaInterruptPrior  (15)
#define SPI5_CPOL               (1)
#define SPI5_CPHA               (1)
#define SPI5_BR                 (SPI_CR1_BR_1)
#define SPI5_DMA_USE            (0)

#define SPI5_DMA_TX             
#define SPI5_DMA_STREAM_TX      
#define SPI5_DMA_STREAM_TX_IRQ  
#define SPI5_DMA_STREAM_TX_IRQ_HANDLER 
#define SPI5_DMA_CHANNEL_TX     
#define SPI5_DMA_CLR_IRQ_TX()   

#define SPI5_DMA_RX             
#define SPI5_DMA_STREAM_RX      
#define SPI5_DMA_STREAM_RX_IRQ  
#define SPI5_DMA_STREAM_RX_IRQ_HANDLER DMA2_Stream0_IRQHandler
#define SPI5_DMA_CHANNEL_RX     
#define SPI5_DMA_CLR_IRQ_RX()   


/*!****************************************************************************
* User enum
*/
typedef enum
{
    SPIState_OK = 0, 
    SPIState_RUN,
    SPIState_TIMEOUT,
    SPIState_HARDERROR,
    SPIState_INVALID_PARAM
}spiState_t;
/*!****************************************************************************
* User typedef
*/
typedef struct{
    SemaphoreHandle_t   semBusy;
    DMA_TypeDef         *dmaTx;
    DMA_TypeDef         *dmaRx;
    SPI_TypeDef         *pSpi;                                 
    DMA_Stream_TypeDef	*pDmaStreamTx;
    DMA_Stream_TypeDef	*pDmaStreamRx;
    uint8_t		        dmaChannelRx	:4;
    uint8_t		        dmaChannelTx	:4;
    spiState_t          state;
}spi_t;
/*!****************************************************************************
* Extern viriables
*/
#if (SPI1_USE > 0)
    extern spi_t spi1;
#endif
#if (SPI1_USE > 0)
    extern spi_t spi5;
#endif
/*!****************************************************************************
* Macro functions
*/
#define SPI_DISABLE(pSPI_t)   pSPI_t->pSpi->CR1 &= ~SPI_CR1_SPE;
#define SPI_ENABLE(pSPI_t)    pSPI_t->pSpi->CR1 |=  SPI_CR1_SPE;
/*!****************************************************************************
* Prototypes for the functions
*/    
    
spiState_t spiTxRxDma(spi_t *spi,uint8_t *src, uint8_t* dst, uint8_t len, uint16_t timeout_ms);
spiState_t spiTxDma(spi_t* spi, uint8_t* src, uint8_t len,  uint16_t timeout_ms);
spiState_t spiTxByte(spi_t* spi, uint8_t byte, uint16_t timeout_ms);
spiState_t spiTxRxByte(spi_t* spi, uint8_t sendByte, uint8_t *receiveByte, uint16_t timeout_ms);

void spiInit(spi_t *spi);


#endif  //!SPIF4_H_
