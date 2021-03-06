#include <stdio.h>
#include <string.h>
#include "Drivers/gpio.h"

#define LCD_DATA    			((uint32_t)0x60200000)    
#define LCD_REG   		  	    ((uint32_t)0x60000000)

void ili9341_InitCommunication(void) {

    RCC->AHB3RSTR |= RCC_AHB3RSTR_FMCRST;
    RCC->AHB3RSTR &= ~RCC_AHB3RSTR_FMCRST;
    RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
    
    gpioInit(GPIOD, 14, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D0
    gpioInit(GPIOD, 15, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D1    
    gpioInit(GPIOD, 0, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //D2
    gpioInit(GPIOD, 1, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //D3
    gpioInit(GPIOE, 7, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //D4
    gpioInit(GPIOE, 8, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //D5
    gpioInit(GPIOE, 9, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //D6
    gpioInit(GPIOE, 10, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D7
    gpioInit(GPIOE, 11, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D8
    gpioInit(GPIOE, 12, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D9
    gpioInit(GPIOE, 13, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D10
    gpioInit(GPIOE, 14, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D11
    gpioInit(GPIOE, 15, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D12
    gpioInit(GPIOD, 8, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //D13
    gpioInit(GPIOD, 9, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //D14
    gpioInit(GPIOD, 10, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0); //D15
    
    gpioInit(GPIOD, 4, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //RD
    gpioInit(GPIOD, 5, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //WR
    gpioInit(GPIOE, 4, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //A20 (LCD D/C)
    gpioInit(GPIOD, 7, gpioMode_OUT, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);  //NE1 (LCD CS)
    
     gpioInit(GPIOD, 3, gpioMode_OUT, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_12, 0);
     GPIO_PIN_SET(GPIOD, 3);
     
    FMC_Bank1E->BWTR[0] |= FMC_BWTR1_ADDSET_1;
    FMC_Bank1E->BWTR[0] |= FMC_BWTR1_DATAST_0 | FMC_BWTR1_DATAST_2;
    FMC_Bank1E->BWTR[0] |= FMC_BWTR1_ACCMOD_0; //Access mode - B
    
    FMC_Bank1->BTCR[0]  &= ~FMC_BCR1_MUXEN;
    FMC_Bank1->BTCR[0]  |= FMC_BCR1_MBKEN;

    //FMC_Bank1->BTCR[0] = 0;
}
void ili9341_WriteData(uint16_t data) {
    *(uint16_t *)(LCD_DATA)= data;
}
void ili9341_WriteData_16(uint16_t data) {
    *(uint16_t *)(LCD_DATA)= data;
}

void ili9341_WriteCommand(uint8_t command) {
    *(uint16_t*)(LCD_REG) = command; 
}
void ili9341_ReadData(uint8_t* response, int count) {
    if (NULL == response){
        return;
    }
    

}
