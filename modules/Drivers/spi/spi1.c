#include "spiPrivate.h"
#include "Drivers/gpio.h"

Spi_t spi1 = 
{
    .pSpiHard = SPI1,
    .pDmaTx = DMA2,
    .pDmaRx = DMA2,
    .pDmaStreamTx = DMA2_Stream3,
    .pDmaStreamRx = DMA2_Stream0,
    .dmaChannelTx = 3,
    .dmaChannelRx = 3,
    .semaphoreBusy = NULL,
    .semaphoreHoldTask = NULL,
    .state = SPI_STATE_NO_INIT
};


__irq void SPI1_IRQHandler(void) 
{
    SpiIrqHandler(&spi1);
}
__irq void DMA2_Stream3_IRQHandler(void) 
{
    if (DMA2->LISR & DMA_LISR_TCIF3)
    {
        DMA2->LIFCR |= DMA_LIFCR_CTCIF3;
        SpiDmaTxIrqHandler(&spi1);
    }
}
__irq void DMA2_Stream0_IRQHandler(void) 
{
    if (DMA2->LISR & DMA_LISR_TCIF0)
    {
        DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
        SpiDmaRxIrqHandler(&spi1);
    }
}


void Spi1_Init(void)
{
    //TODO: gpioInit need to another file!


    // ====== INIT MEMORY  ====== //
    spi1.semaphoreBusy = xSemaphoreCreateBinary();
    if (NULL == spi1.semaphoreBusy)
    {
        return;
    }

    spi1.semaphoreHoldTask = xSemaphoreCreateBinary();
    if (NULL == spi1.semaphoreHoldTask)
    {
        return;
    }

    // ====== INIT SPI clock  ====== //
    RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // ====== INIT SPI PARAMS  ====== //
    //spi1.pSpiHard->CR1 |= SPI1_BR;

    spi1.pSpiHard->CR1 |= SPI_CR1_SSI;
    spi1.pSpiHard->CR1 |= SPI_CR1_SSM;
    spi1.pSpiHard->CR1 |= SPI_CR1_MSTR;


    
    //DMA SPI TX
    spi1.pDmaStreamTx->CR |= (uint32_t)((spi1.dmaChannelTx & 0x03) << 25);    //Channel selection
    spi1.pDmaStreamTx->CR |= DMA_SxCR_PL_1;	                                //Priority level High
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_MSIZE;	                                //Memory data size 8 bit
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_PSIZE;	                                //Memory data size 8 bit
    spi1.pDmaStreamTx->CR |= DMA_SxCR_MINC;	                                //Memory increment mode enebled
    spi1.pDmaStreamTx->CR &= ~DMA_SxCR_PINC;	                                //Peripheral increment mode disabled
    spi1.pDmaStreamTx->CR |= DMA_SxCR_DIR_0;	                                //Direction Memory-to-peripheral
    //spi1.pDmaStreamTx->CR |= DMA_SxCR_TCIE;	                                //Transfer complete interrupt enable
    spi1.pDmaStreamTx->PAR = (uint32_t)&spi1.pSpiHard->DR;

    //DMA SPI RX
    spi1.pDmaStreamRx->CR |= (uint32_t)((spi1.dmaChannelRx & 0x03) << 25);    //Channel selection
    spi1.pDmaStreamRx->CR |= DMA_SxCR_PL_1;				        //Priority level High
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_MSIZE;				        //Memory data size 8 bit
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_PSIZE;				        //Memory data size 8 bit
    spi1.pDmaStreamRx->CR |= DMA_SxCR_MINC;				        //Memory increment mode enebled
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_PINC;				        //Peripheral increment mode disabled
    spi1.pDmaStreamRx->CR &= ~DMA_SxCR_DIR;				        //Direction Peripheral-to-memory
    //spi1.pDmaStreamRx->CR |= DMA_SxCR_TCIE;				        //Transfer complete interrupt enable
    spi1.pDmaStreamRx->PAR = (uint32_t)&spi1.pSpiHard->DR;

    // ====== INIT  NVIC  ====== //
    NVIC_EnableIRQ(SPI1_IRQn);
    NVIC_SetPriority(SPI1_IRQn, 15); //TODO: need out in global file

    
    NVIC_EnableIRQ(DMA2_Stream3_IRQn);		//RX
    NVIC_SetPriority(DMA2_Stream3_IRQn, 15);//TODO: need out in global file
    NVIC_EnableIRQ(DMA2_Stream0_IRQn);		//TX
    NVIC_SetPriority(DMA2_Stream0_IRQn, 15);//TODO: need out in global file
    
    // ====== SPI ENABLE  ====== //
    spi1.pSpiHard->CR1 |= SPI_CR1_SPE;
    
    spi1.state = SPI_STATE_OK;
}


