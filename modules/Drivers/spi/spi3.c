#include "stm32f4xx.h"
#include "Drivers/gpio.h"

#define SPI3_SCK_PORT   GPIOB
#define SPI3_SCK_PIN    3
#define SPI3_SCK_AF     6
#define SPI3_MISO_PORT  GPIOB
#define SPI3_MISO_PIN   4
#define SPI3_MISO_AF    6
#define SPI3_MOSI_PORT  GPIOB
#define SPI3_MOSI_PIN   5
#define SPI3_MOSI_AF    6

void spi3Init(void) {
    // -- GPIO-- //
    gpioInit(SPI3_SCK_PORT,  SPI3_SCK_PIN,  gpioMode_AF, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, (gpioAF)SPI3_SCK_AF,  0);
    gpioInit(SPI3_MISO_PORT, SPI3_MISO_PIN, gpioMode_AF, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, (gpioAF)SPI3_MISO_AF, 0);
    gpioInit(SPI3_MOSI_PORT, SPI3_MOSI_PIN, gpioMode_AF, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, (gpioAF)SPI3_MOSI_AF, 0);

    // -- RCC -- //
    RCC->APB1RSTR|= RCC_APB1RSTR_SPI3RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI3RST;
    RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;

    SPI3->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
    
    SPI3->CR1 |= SPI_CR1_SSI;
    SPI3->CR1 |= SPI_CR1_SSM;
    SPI3->CR1 |= SPI_CR1_MSTR;

    // ====== SPI ENABLE  ====== //
    SPI3->CR1 |= SPI_CR1_SPE;
}
void spi3Tranceive(uint8_t byte) {
    SPI3->DR = byte;
}