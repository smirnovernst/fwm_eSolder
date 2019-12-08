#include "stm32f4xx.h"
#include "Drivers/spiF4.h"
#include "Drivers/gpio.h"

#define F_SPI_TRANCEIVE(byte)   spiTxByte(&spi3, byte, 100);

#define ILI9341_DCX_PORT        GPIOE
#define ILI9341_DCX_PIN         4
#define ILI9341_CS_PORT         GPIOE
#define ILI9341_CS_PIN          0

void ili9341_InitCommunication(void) {
    gpioInit(ILI9341_DCX_PORT, ILI9341_DCX_PIN, gpioMode_OUT, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_None, 0);
    gpioInit(ILI9341_CS_PORT, ILI9341_CS_PIN, gpioMode_OUT, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_None, 1);
    
    gpioInit(GPIOB, 3, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, (gpioAF)6, 0);
    gpioInit(GPIOB, 5, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, (gpioAF)6, 0);
    
    spiInit(&spi3);
}
void ili9341_WriteData(uint8_t data) {
    GPIO_PIN_SET(ILI9341_DCX_PORT, ILI9341_DCX_PIN);
    F_SPI_TRANCEIVE(data);
}
void ili9341_WriteData_16(uint16_t data) {
    ili9341_WriteData(*((uint8_t*)&data + 1));
    ili9341_WriteData(*((uint8_t*)&data));
}
void ili9341_WriteCommand(uint8_t command) {
    GPIO_PIN_SET(ILI9341_CS_PORT, ILI9341_CS_PIN);
    GPIO_PIN_RESET(ILI9341_CS_PORT, ILI9341_CS_PIN);
    GPIO_PIN_RESET(ILI9341_DCX_PORT, ILI9341_DCX_PIN);
    F_SPI_TRANCEIVE(command);
}
void ili9341_ReadData(uint8_t* response, int count) {

}
