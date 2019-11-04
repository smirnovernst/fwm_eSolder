#include "Drivers/gpio.h"

void gpioInit (GPIO_TypeDef *port, gpioPin_t pin,  gpioMode_t mode, gpioPuPd_t PuPd, gpioType_t type, gpioAF afNum, uint8_t initState)
{
   uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

 

  /* ------------------------- Configure the port pins ---------------- */
  /*-- GPIO mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (pin) & pos;

    if (currentpin == pos)
    {
      port->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      port->PUPDR |= ((PuPd) << (pinpos * 2));
      
      port->OTYPER &= ~(GPIO_OTYPER_OT_0 << (uint16_t)pinpos);
      port->OTYPER |= ((type) << pinpos);

      port->ODR ^= (initState > 0);

      port->MODER &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
      port->MODER |= (((uint32_t)mode) << (pinpos * 2));
      if(mode == gpioMode_AF){
          gpioAfInit(port, pinpos, afNum);
      }
    }
  }
  port->OSPEEDR = 0xFFFFFFFF;
  
}


void gpioAfInit (GPIO_TypeDef *port, uint8_t pin, gpioAF afNum)
{
    if (afNum >= gpioAF_None) return;

    uint32_t Low = 0, High = 0;
 
    Low = ((uint32_t)(afNum) << ((uint32_t)((uint32_t)pin & (uint32_t)0x07) * 4)) ;
    port->AFR[pin >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)pin & (uint32_t)0x07) * 4)) ;
    High = port->AFR[pin >> 0x03] | Low;
    port->AFR[pin >> 0x03] = High;

}


 