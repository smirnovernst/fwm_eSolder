/*
*@File          spi_f4.c
*@Author        Ernst
*@Version       
*@Date          22.08.2018
*@Breif         
*/
/*!****************************************************************************
* Include
*/
#include "spi_f4.h"

#include "GPIO.h"
#include "assert.h"
/*!****************************************************************************
* Memory
*/
#if (SPI1_USE > 0)
    spi_t spi1;
#endif

/*!****************************************************************************
* Functions prototype
*/
void spi_DmaRxIrqHandler(spi_t* spi);
void spi_DmaTxIrqHandler(spi_t* spi);
/*!****************************************************************************
* IRQ
*/
__irq void SPI1_IRQHandler(void) {
    spi_IrqHandler(SPI1);
}
/*!****************************************************************************
* Functions
*/

void spi_DmaTxIrqHandler(spi_t *spi)
{ 
    if (spi->pSpi->SR )
    BaseType_t  xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(spi->semaph_tx, &xHigherPriorityTaskWoken);
    if(xHigherPriorityTaskWoken != pdFALSE)
    {
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
    
}
void spi_DmaRxIrqHandler(spi_t *spi)
{ 
    BaseType_t  xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(spi->semaph_rx, &xHigherPriorityTaskWoken);
    if(xHigherPriorityTaskWoken != pdFALSE)
    {
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
}
void spi_IrqHandler(spi_t *spi)
{ 
    if ( (spi->pSpi->SR && SPI_SR_OVR) || (spi->pSpi->SR && SPI_SR_MODF) || (spi->pSpi->SR && SPI_SR_UDR) )
    {
        BaseType_t  xHigherPriorityTaskWoken;
        xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(spi->semaph_rx, &xHigherPriorityTaskWoken);
        if(xHigherPriorityTaskWoken != pdFALSE)
        {
            portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
        }
        xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(spi->semaph_tx, &xHigherPriorityTaskWoken);
        if(xHigherPriorityTaskWoken != pdFALSE)
        {
            portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
        }
        
        spi->state = SPIState_hardErr;
        spi->pSpi->SR &= (~SPI_SR_OVR) & (~SPI_SR_MODF) & (~SPI_SR_UDR);
    }
}
uint8_t spi_receive(spi_t *spi, uint8_t* dst, uint8_t len, uint16_t timeout)
{
    spi->pDmaStreamRx->CR	&= ~DMA_SxCR_EN;
    spi->pDmaStreamRx->M0AR	= (uint32_t)dst;
    spi->pDmaStreamRx->NDTR	= len;
    spi->pDmaStreamRx->CR |= DMA_SxCR_EN;
     
    BaseType_t	res;
    res = xSemaphoreTake(spi->semaph_rx, timeout/portTICK_PERIOD_MS);
    if(res != pdTRUE){
        return SPIState_Timeout;
    }
   
    
    return 0;
}
uint8_t spi_tranceive(spi_t *spi, uint8_t* src, uint8_t len, uint16_t timeout)
{
    BaseType_t	res;
    res = xSemaphoreTake(spi->semaph_tx,  timeout/portTICK_PERIOD_MS);
    if(res != pdTRUE){
        return SPIState_Timeout;
    }
    
    spi->pDmaStreamTx->CR	&= ~DMA_SxCR_EN;
    spi->pDmaStreamTx->M0AR	= (uint32_t)src;
    spi->pDmaStreamTx->NDTR	= len;
    spi->pDmaStreamTx->CR |= DMA_SxCR_EN;
    
    return 0;
}

void spi_init()
{
    
#if (SPI1_USE > 0)
    // ====== INIT MEMORY  ====== //
    spi1.pSpi		= SPI1;
    spi1.pDmaStreamTx	= SPI1_DMA_STREAM_TX;
    spi1.pDmaStreamRx	= SPI1_DMA_STREAM_RX;
    spi1.dmaChannelTx	= SPI1_DMA_CHANNEL_TX;
    spi1.dmaChannelRx	= SPI1_DMA_CHANNEL_RX;

    vSemaphoreCreateBinary(spi1.semaph_rx);
    assert(spi1.semaph_rx != NULL);
    vSemaphoreCreateBinary(spi1.semaph_tx);
    assert(spi1.semaph_tx != NULL);
    
    xSemaphoreTake(spi1.semaph_rx, portMAX_DELAY);
    // ====== INIT GPIO  ====== //
    gpioInit(SPI1_SCK_PORT,  SPI1_SCK_PIN,  gpioMode_AF, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, SPI1_SCK_AF, 0);
    gpioInit(SPI1_MISO_PORT, SPI1_MISO_PIN, gpioMode_AF, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, SPI1_MISO_AF,0);
    gpioInit(SPI1_MOSI_PORT, SPI1_MOSI_PIN, gpioMode_AF, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, SPI1_MOSI_AF,0);

    // ====== INIT SPI clock  ====== //
    RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    
    // ====== INIT SPI PARAMS  ====== //
    spi1.pSpi->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
       
    spi1.pSpi->CR1 |= SPI_CR1_SSI;
    spi1.pSpi->CR1 |= SPI_CR1_SSM;
    spi1.pSpi->CR1 |= SPI_CR1_MSTR;
    
    if (SPI1_CPHA) {  spi1.pSpi->CR1 |= SPI_CR1_CPHA; }
    if (SPI1_CPOL) {  spi1.pSpi->CR1 |= SPI_CR1_CPOL; }                                    

    //spi_SPI1.pSpi->CR2 |= SPI_CR2_ERRIE;
    spi1.pSpi->CR2 |= SPI_CR2_TXDMAEN;
    spi1.pSpi->CR2 |= SPI_CR2_RXDMAEN;
    
    // ====== INIT  DMA  ====== //
    //DMA SPI TX
    spi1.pDmaStreamTx->CR |= (uint32_t)((spi1.dmaChannelTx & 0x03) << 25);    //Channel selection
    spi1.pDmaStreamTx->CR |= DMA_SxCR_PL_1;	                                //Priority level High
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_MSIZE;	                                //Memory data size 8 bit
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_PSIZE;	                                //Memory data size 8 bit
    spi1.pDmaStreamTx->CR |= DMA_SxCR_MINC;	                                //Memory increment mode enebled
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_PINC;	                                //Peripheral increment mode disabled
    spi1.pDmaStreamTx->CR |= DMA_SxCR_DIR_0;	                                //Direction Memory-to-peripheral
    spi1.pDmaStreamTx->CR |= DMA_SxCR_TCIE;	                                //Transfer complete interrupt enable
    spi1.pDmaStreamTx->PAR = (uint32_t)&spi1.pSpi->DR;

    //DMA SPI RX
    spi1.pDmaStreamRx->CR |= (uint32_t)((spi1.dmaChannelRx & 0x03) << 25);    //Channel selection
    spi1.pDmaStreamRx->CR |= DMA_SxCR_PL_1;				        //Priority level High
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_MSIZE;				        //Memory data size 8 bit
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_PSIZE;				        //Memory data size 8 bit
    spi1.pDmaStreamRx->CR |= DMA_SxCR_MINC;				        //Memory increment mode enebled
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_PINC;				        //Peripheral increment mode disabled
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_DIR;				        //Direction Peripheral-to-memory
    spi1.pDmaStreamRx->CR |= DMA_SxCR_TCIE;				        //Transfer complete interrupt enable
    spi1.pDmaStreamRx->PAR = (uint32_t)&spi1.pSpi->DR;
    
    // ====== INIT  NVIC  ====== //
    NVIC_EnableIRQ(SPI1_IRQn);
    NVIC_SetPriority(SPI1_IRQn, SPI1_InterruptPrior);
  
    NVIC_EnableIRQ(DMA2_Stream0_IRQn);		//RX
    NVIC_SetPriority(DMA2_Stream0_IRQn, SPI1_InterruptPrior);
    NVIC_EnableIRQ(DMA2_Stream3_IRQn);		//TX
    NVIC_SetPriority(DMA2_Stream3_IRQn, SPI1_DmaInterruptPrior);

    // ====== SPI ENABLE  ====== //
    spi1.pSpi->CR1 |= SPI_CR1_SPE;
#endif
}
