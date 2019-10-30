/*!****************************************************************************
* @file    GPIO_h.h
* @author  ЭрикМарина
* @version V1.0
* @date    15.04.2016
* @brief   --
*/
#ifndef GPIO_h_H
#define GPIO_h_H

/*!****************************************************************************
* Include
*/
#include "global_inc.h"

/*!****************************************************************************
* User define
*/

/*!****************************************************************************
* User enum
*/
typedef enum
{
  gpioMode_IN =0,
  gpioMode_OUT,
  gpioMode_AF,
  gpioMode_ANALOG,
}gpioMode_t;

typedef enum
{
  gpioPuPd_NOPULL   = 0,
  gpioPuPd_PULLUP   = 1,
  gpioPuPd_PULLDOWN = 2,
  gpioPuPd_RESERVED = 3
} gpioPuPd_t;

typedef enum
{
  gpioType_PUSHPULL = 0,
  gpioType_OPENDRAIN = 1,
} gpioType_t;
/*!****************************************************************************
* User typedef
*/
typedef struct
{
    GPIO_TypeDef *port;
    uint8_t pinNum;
    gpioMode_t mode;
    gpioPuPd_t PuPd;
    gpioType_t type;
    uint8_t afNum;
    uint8_t initState;
}gpioParam_t;
/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/
#define GPIO_PIN_SET(port, pin)        (port->BSRRL |= (1 << pin))
#define GPIO_PIN_RESET(port, pin)      (port->BSRRH |= (1 << pin))
#define GPIO_PIN_GET(port, pin)        (port->IDR & (pin))
#define GPIO_PIN_TOGLE(port, pin)      (port->ODR ^= (pin))
/*!****************************************************************************
* Prototypes for the functions
*/

void gpioInitTbl(gpioParam_t *gpioParam, uint8_t size);
void gpioInit (GPIO_TypeDef *port, uint8_t pinNum,  gpioMode_t mode, gpioPuPd_t PuPd, gpioType_t type, uint8_t afNum, uint8_t initState);
void gpioAfInit (GPIO_TypeDef *port, uint8_t pin, uint8_t afNum);
 
#endif //GPIO_h_H
/***************** (C) COPYRIGHT ************** END OF FILE ******** ЭрикМарина ****/