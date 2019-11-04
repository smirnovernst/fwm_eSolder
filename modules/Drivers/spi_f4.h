/*
*@File          spi_f4.h
*@Author        Ernst
*@Version       
*@Date          22.08.2018
*@Breif         
*/
#ifndef  spi_f4_h
#define  spi_f4_h
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
#define SPI1_DMA_STREAM_TX      (DMA2_Stream3)
#define SPI1_DMA_STREAM_RX      (DMA2_Stream0)
#define SPI1_DMA_CHANNEL_TX     (3)
#define SPI1_DMA_CHANNEL_RX     (3)
//   PINS 
#define SPI1_SCK_PORT           (GPIOB)
#define SPI1_SCK_PIN            (3)
#define SPI1_SCK_AF             (5)

#define SPI1_MISO_PORT          (GPIOB)
#define SPI1_MISO_PIN           (4)
#define SPI1_MISO_AF            (5)

#define SPI1_MOSI_PORT          (GPIOB)
#define SPI1_MOSI_PIN           (5)
#define SPI1_MOSI_AF            (5)

/*!****************************************************************************
* User enum
*/
/*!****************************************************************************
* User typedef
*/
typedef enum
{
    SPIState_Ok = 0, 
    SPIState_Timeout,
    SPIState_hardErr,
}spiState_t;

typedef struct
{
    SemaphoreHandle_t   semaph_rx;
    SemaphoreHandle_t   semaph_tx;
    SPI_TypeDef         *pSpi;                                 
    DMA_Stream_TypeDef	*pDmaStreamTx;
    DMA_Stream_TypeDef	*pDmaStreamRx;
    uint8_t		dmaChannelRx	:4;
    uint8_t		dmaChannelTx	:4;
    spiState_t          state;
}spi_t;
/*!****************************************************************************
* Extern viriables
*/
#if (SPI1_USE > 0)
    extern spi_t spi1;
#endif
/*!****************************************************************************
* Macro functions
*/
#define SPI_DISABLE(pSPI_t)   pSPI_t->pSpi->CR1 &= ~SPI_CR1_SPE;
#define SPI_ENABLE(pSPI_t)    pSPI_t->pSpi->CR1 |=  SPI_CR1_SPE;
/*!****************************************************************************
* Prototypes for the functions
*/    
    
uint8_t spi_receive(spi_t *spi, uint8_t* dst, uint8_t len, uint16_t timeout);
uint8_t spi_tranceive(spi_t *spi, uint8_t* src, uint8_t len, uint16_t timeout);


void spi_IrqHandler(spi_t *spi);
void spi_init(SPI_TypeDef *spi);


#endif  //spi_f4_h
