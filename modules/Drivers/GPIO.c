#include "Drivers/gpio.h"
#include <assert.h>

#define GPIO_MAX_PIN 15

void gpioInit (GPIO_TypeDef *port, uint8_t pinNum,  gpioMode_t mode, gpioPuPd_t PuPd, gpioType_t type, gpioAF afNum, uint8_t initState)
{
    assert(pinNum <= GPIO_MAX_PIN);
    
    port->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinNum * 2));
    port->PUPDR |= ((PuPd) << (pinNum * 2));
    
    port->OTYPER &= ~(GPIO_OTYPER_OT_0 << (uint16_t)pinNum);
    port->OTYPER |= ((type) << pinNum);
    
    port->ODR ^= (initState > 0);
    
    port->MODER &= ~(GPIO_MODER_MODER0 << (pinNum * 2));
    port->MODER |= (((uint32_t)mode) << (pinNum * 2));
    
    if(mode == gpioMode_AF){
        gpioAfInit(port, pinNum, afNum);
    }
    port->OSPEEDR = 0xFFFFFFFF;
    
}


void gpioAfInit (GPIO_TypeDef *port, uint8_t pinNum, gpioAF afNum)
{
    assert(afNum < gpioAF_None);
    assert(pinNum <= GPIO_MAX_PIN);

    uint32_t Low = 0, High = 0;
 
    Low = ((uint32_t)(afNum) << ((uint32_t)((uint32_t)pinNum & (uint32_t)0x07) * 4)) ;
    port->AFR[pinNum >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)pinNum & (uint32_t)0x07) * 4)) ;
    High = port->AFR[pinNum >> 0x03] | Low;
    port->AFR[pinNum >> 0x03] = High;

}


 