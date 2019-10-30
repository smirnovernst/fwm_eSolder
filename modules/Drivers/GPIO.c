#include "GPIO.h"



void gpioInit(GPIO_TypeDef *port, uint8_t pinNum,  gpioMode_t mode, gpioPuPd_t PuPd, gpioType_t type, uint8_t afNum, uint8_t initState)
{
    //Clock enable
    if(port == GPIOA)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if(port == GPIOB)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if(port == GPIOC)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if(port == GPIOD)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if(port == GPIOE)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    else if(port == GPIOF)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    else if(port == GPIOG)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    else if(port == GPIOH)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    else if(port == GPIOI)	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    
    //Set initial value
    if(initState != 0){
        GPIO_PIN_SET(port, pinNum);
    }
    else{
        GPIO_PIN_RESET(port, pinNum);
    }
    
    //Clear bit field
    port->MODER	 &= ~(0x03 << (2 * pinNum));
    port->OTYPER &= ~(1<<pinNum);
    port->PUPDR	 &= ~(gpioPuPd_RESERVED << (2 * pinNum));
    port->AFR[pinNum / 8] &= ~(0x0F << (4 * (pinNum % 8)));
    
    //Set number alternate function
    port->AFR[pinNum / 8] |= afNum << (4 * (pinNum % 8));
    

    
    // Set mode
    port->PUPDR     |= PuPd << (2 * pinNum);
    port->MODER	    |= mode << (2 * pinNum);
    port->OTYPER    |= type << pinNum;
    port->OSPEEDR	|= 3 << (2 * pinNum);	  //High speed
    
    
    
    
    
    
}


void gpioAfInit (GPIO_TypeDef *port, uint8_t pin, uint8_t afNum)
{
    uint32_t Low = 0, High = 0;
    
    Low = ((uint32_t)(afNum) << ((uint32_t)((uint32_t)pin & (uint32_t)0x07) * 4)) ;
    port->AFR[pin >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)pin & (uint32_t)0x07) * 4)) ;
    High = port->AFR[pin >> 0x03] | Low;
    port->AFR[pin >> 0x03] = High;
    
}


