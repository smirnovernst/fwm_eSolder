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
#include "spiF4.h"

#include "GPIO.h"
#include "assert.h"
/*!****************************************************************************
* Memory
*/
#if (SPI1_USE > 0)
    spi_t spi1;
#endif
#if (SPI5_USE > 0)
    spi_t spi5;
#endif

/*!****************************************************************************
* Functions prototype
*/
void spi_DmaRxIrqHandler(spi_t* spi);
void spi_DmaTxIrqHandler(spi_t* spi);
void spi_IrqHandler(spi_t *spi);
/*!****************************************************************************
* IRQ
*/

__irq void SPI1_IRQHandler(void) {
    spi_IrqHandler(&spi1);
}
#if SPI1_DMA_USE
__irq void SPI1_DMA_STREAM_TX_IRQ_HANDLER(void) {
    SPI1_DMA_CLR_IRQ_TX();
    spi_DmaTxIrqHandler(&spi1);
}
__irq void SPI1_DMA_STREAM_RX_IRQ_HANDLER(void) {
    SPI1_DMA_CLR_IRQ_RX();
    spi_DmaTxIrqHandler(&spi1);
}
#endif

__irq void SPI5_IRQHandler(void) {
    spi_IrqHandler(&spi5);
}
#if SPI5_DMA_USE
__irq void SPI5_DMA_STREAM_TX_IRQ_HANDLER(void) {
    SPI5_DMA_CLR_IRQ_TX();
    spi_DmaTxIrqHandler(&spi5);
}
__irq void SPI1_DMA_STREAM_RX_IRQ_HANDLER(void) {
    SPI5_DMA_CLR_IRQ_RX();
    spi_DmaTxIrqHandler(&spi5);
}
#endif
/*!****************************************************************************
* Functions
*/

void spi_DmaTxIrqHandler(spi_t *spi){ 
    spi->pDmaStreamTx->CR &= ~DMA_SxCR_TCIE;
    spi->state = SPIState_OK;

    BaseType_t  xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(spi->semBusy, &xHigherPriorityTaskWoken);
    if(xHigherPriorityTaskWoken != pdFALSE){
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
    
}
void spi_DmaRxIrqHandler(spi_t *spi){ 
    spi->pDmaStreamRx->CR &= ~DMA_SxCR_TCIE; 
    spi->state = SPIState_OK;

    BaseType_t  xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(spi->semBusy, &xHigherPriorityTaskWoken);
    if(xHigherPriorityTaskWoken != pdFALSE){
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
}
void spi_IrqHandler(spi_t *spi){ 
    if ( (spi->pSpi->SR && SPI_SR_OVR) || (spi->pSpi->SR && SPI_SR_MODF) || (spi->pSpi->SR && SPI_SR_UDR) ){
        spi->state = SPIState_HARDERROR;
        spi->pSpi->SR &= (~SPI_SR_OVR) & (~SPI_SR_MODF) & (~SPI_SR_UDR);
        spi->pSpi->DR;
        spi->pDmaStreamTx->CR &= ~DMA_SxCR_EN;
        spi->pDmaStreamRx->CR &= ~DMA_SxCR_EN;

        BaseType_t  xHigherPriorityTaskWoken;
        xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(spi->semBusy, &xHigherPriorityTaskWoken);
        if (xHigherPriorityTaskWoken != pdFALSE){
            portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
        }
    }
}





void spiInit(spi_t* spi) {
#if (SPI1_USE > 0)
    // ====== INIT MEMORY  ====== //
    spi1.pSpi = SPI1;
    spi1.pDmaStreamTx = SPI1_DMA_STREAM_TX;
    spi1.pDmaStreamRx = SPI1_DMA_STREAM_RX;
    spi1.dmaChannelTx = SPI1_DMA_CHANNEL_TX;
    spi1.dmaChannelRx = SPI1_DMA_CHANNEL_RX;
    spi1.dmaRx = SPI1_DMA_RX;
    spi1.dmaTx = SPI1_DMA_TX;
    vSemaphoreCreateBinary(spi1.semBusy);
    assert(spi1.semBusy != NULL);

    // ====== INIT SPI clock  ====== //
    RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // ====== INIT SPI PARAMS  ====== //
    spi1.pSpi->CR1 |= SPI1_BR;

    spi1.pSpi->CR1 |= SPI_CR1_SSI;
    spi1.pSpi->CR1 |= SPI_CR1_SSM;
    spi1.pSpi->CR1 |= SPI_CR1_MSTR;

    if (SPI1_CPHA) { spi1.pSpi->CR1 |= SPI_CR1_CPHA; }
    if (SPI1_CPOL) { spi1.pSpi->CR1 |= SPI_CR1_CPOL; }

    // ====== INIT  DMA  ====== //
    #if SPI1_DMA_USE
    //DMA SPI TX
    spi1.pDmaStreamTx->CR |= (uint32_t)((spi1.dmaChannelTx & 0x03) << 25);    //Channel selection
    spi1.pDmaStreamTx->CR |= DMA_SxCR_PL_1;	                                //Priority level High
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_MSIZE;	                                //Memory data size 8 bit
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_PSIZE;	                                //Memory data size 8 bit
    spi1.pDmaStreamTx->CR |= DMA_SxCR_MINC;	                                //Memory increment mode enebled
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_PINC;	                                //Peripheral increment mode disabled
    spi1.pDmaStreamTx->CR |= DMA_SxCR_DIR_0;	                                //Direction Memory-to-peripheral
    //spi1.pDmaStreamTx->CR |= DMA_SxCR_TCIE;	                                //Transfer complete interrupt enable
    spi1.pDmaStreamTx->PAR = (uint32_t)&spi1.pSpi->DR;

    //DMA SPI RX
    spi1.pDmaStreamRx->CR |= (uint32_t)((spi1.dmaChannelRx & 0x03) << 25);    //Channel selection
    spi1.pDmaStreamRx->CR |= DMA_SxCR_PL_1;				        //Priority level High
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_MSIZE;				        //Memory data size 8 bit
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_PSIZE;				        //Memory data size 8 bit
    spi1.pDmaStreamRx->CR |= DMA_SxCR_MINC;				        //Memory increment mode enebled
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_PINC;				        //Peripheral increment mode disabled
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_DIR;				        //Direction Peripheral-to-memory
    //spi1.pDmaStreamRx->CR |= DMA_SxCR_TCIE;				        //Transfer complete interrupt enable
    spi1.pDmaStreamRx->PAR = (uint32_t)&spi1.pSpi->DR;
    #endif
    // ====== INIT  NVIC  ====== //
    NVIC_EnableIRQ(SPI1_IRQn);
    NVIC_SetPriority(SPI1_IRQn, SPI1_InterruptPrior);

    #if SPI1_DMA_USE
    NVIC_EnableIRQ(SPI1_DMA_STREAM_RX_IRQ);		//RX
    NVIC_SetPriority(SPI1_DMA_STREAM_RX_IRQ, SPI1_InterruptPrior);
    NVIC_EnableIRQ(SPI1_DMA_STREAM_TX_IRQ);		//TX
    NVIC_SetPriority(SPI1_DMA_STREAM_TX_IRQ, SPI1_DmaInterruptPrior);
    #endif
    // ====== SPI ENABLE  ====== //
    spi1.pSpi->CR1 |= SPI_CR1_SPE;
#endif
    //####################################################
#if (SPI5_USE > 0)
    // ====== INIT MEMORY  ====== //
    spi5.pSpi = SPI5;
    
    #if SPI5_DMA_USE
        spi5.pDmaStreamTx = SPI5_DMA_STREAM_TX;
        spi5.pDmaStreamRx = SPI5_DMA_STREAM_RX;
        spi5.dmaChannelTx = SPI5_DMA_CHANNEL_TX;
        spi5.dmaChannelRx = SPI5_DMA_CHANNEL_RX;
        spi5.dmaRx = SPI5_DMA_RX;
        spi5.dmaTx = SPI5_DMA_TX;
    #endif
    vSemaphoreCreateBinary(spi5.semBusy);
    assert(spi5.semBusy != NULL);

    // ====== INIT SPI clock  ====== //
    RCC->APB2RSTR |= RCC_APB2RSTR_SPI5RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI5RST;
    RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;

    // ====== INIT SPI PARAMS  ====== //
    spi5.pSpi->CR1 |= SPI5_BR;

    spi5.pSpi->CR1 |= SPI_CR1_SSI;
    spi5.pSpi->CR1 |= SPI_CR1_SSM;
    spi5.pSpi->CR1 |= SPI_CR1_MSTR;

    if (SPI5_CPHA) { spi5.pSpi->CR1 |= SPI_CR1_CPHA; }
    if (SPI5_CPOL) { spi5.pSpi->CR1 |= SPI_CR1_CPOL; }

    // ====== INIT  DMA  ====== //
    #if SPI5_DMA_USE
    //DMA SPI TX
    spi5.pDmaStreamTx->CR |= (uint32_t)((spi5.dmaChannelTx & 0x03) << 25);    //Channel selection
    spi5.pDmaStreamTx->CR |= DMA_SxCR_PL_1;	                                //Priority level High
    spi5.pDmaStreamTx->CR &= ~DMA_SxCR_MSIZE;	                                //Memory data size 8 bit
    spi5.pDmaStreamTx->CR &= ~DMA_SxCR_PSIZE;	                                //Memory data size 8 bit
    spi5.pDmaStreamTx->CR |= DMA_SxCR_MINC;	                                //Memory increment mode enebled
    spi5.pDmaStreamTx->CR &= ~DMA_SxCR_PINC;	                                //Peripheral increment mode disabled
    spi5.pDmaStreamTx->CR |= DMA_SxCR_DIR_0;	                                //Direction Memory-to-peripheral
    spi5.pDmaStreamTx->PAR = (uint32_t)&spi5.pSpi->DR;

    //DMA SPI RX
    spi5.pDmaStreamRx->CR |= (uint32_t)((spi5.dmaChannelRx & 0x03) << 25);    //Channel selection
    spi5.pDmaStreamRx->CR |= DMA_SxCR_PL_1;				        //Priority level High
    spi5.pDmaStreamRx->CR &= ~DMA_SxCR_MSIZE;				        //Memory data size 8 bit
    spi5.pDmaStreamRx->CR &= ~DMA_SxCR_PSIZE;				        //Memory data size 8 bit
    spi5.pDmaStreamRx->CR |= DMA_SxCR_MINC;				        //Memory increment mode enebled
    spi5.pDmaStreamRx->CR &= ~DMA_SxCR_PINC;				        //Peripheral increment mode disabled
    spi5.pDmaStreamRx->CR &= ~DMA_SxCR_DIR;				        //Direction Peripheral-to-memory

    spi5.pDmaStreamRx->PAR = (uint32_t)&spi5.pSpi->DR;
    #endif
    // ====== INIT  NVIC  ====== //
    NVIC_EnableIRQ(SPI5_IRQn);
    NVIC_SetPriority(SPI5_IRQn, SPI5_InterruptPrior);

    #if SPI5_DMA_USE
    NVIC_EnableIRQ(SPI5_DMA_STREAM_RX_IRQ);		//RX
    NVIC_SetPriority(SPI5_DMA_STREAM_RX_IRQ, SPI5_InterruptPrior);
    NVIC_EnableIRQ(SPI5_DMA_STREAM_TX_IRQ);		//TX
    NVIC_SetPriority(SPI5_DMA_STREAM_TX_IRQ, SPI5_DmaInterruptPrior);
    #endif
    // ====== SPI ENABLE  ====== //
    spi5.pSpi->CR1 |= SPI_CR1_SPE;
#endif
}
