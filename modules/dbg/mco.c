#include "dbg/mco.h"
#include "Drivers/gpio.h"

#define MCO2_PORT   GPIOC
#define MCO2_PIN    9
#define MCO2_AF     0

void MCO2Enable(MCO2_t mode, MCOPrescaller_t prsc){
    RCC->CFGR |= mode << RCC_CFGR_MCO2;
    RCC->CFGR |= prsc << RCC_CFGR_MCO2PRE;
    gpioInit(MCO2_PORT, MCO2_PIN, gpioMode_AF, gpioPuPd_NOPULL, gpioType_PUSHPULL, (gpioAF)MCO2_AF, 0);
}