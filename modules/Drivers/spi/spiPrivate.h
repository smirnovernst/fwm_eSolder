#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#include "spi.h"

#define SPI_RXDMA_IRQ_ENABLE(pSpi)  (pSpi->pDmaStreamRx->CR |= DMA_SxCR_TCIE)
#define SPI_RXDMA_IRQ_DISABLE(pSpi) (pSpi->pDmaStreamRx->CR &= ~DMA_SxCR_TCIE)

#define SPI_TXDMA_IRQ_ENABLE(pSpi)  (pSpi->pDmaStreamTx->CR &= ~DMA_SxCR_TCIE)
#define SPI_TXDMA_IRQ_DISABLE(pSpi) (pSpi->pDmaStreamTx->CR &= ~DMA_SxCR_TCIE)

#define SPI_RXNE_IRQ_ENABLE(pSpi)   (pSpi->pSpiHard->CR2 |= SPI_CR2_RXNEIE)
#define SPI_RXNE_IRQ_DISABLE(pSpi)  (pSpi->pSpiHard->CR2 &= ~SPI_CR2_RXNEIE)

void SpiDmaTxIrqHandler(Spi_t *pSpi);
void SpiDmaRxIrqHandler(Spi_t *pSpi);
void SpiIrqHandler(Spi_t *pSpi);

#endif //!SPI_PRIVATE_H_