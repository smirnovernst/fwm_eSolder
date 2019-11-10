/*!****************************************************************************
* @file    GPIO_h.h
* @author  ЭрикМарина
* @version V1.0
* @date    15.04.2016
* @brief   --
*/
#ifndef GPIO_H_
#define GPIO_H_

/*!****************************************************************************
* Include
*/
#include "stm32f4xx.h"

/*!****************************************************************************
* User define
*/

/*!****************************************************************************
* User enum
*/
typedef enum{
  gpioPin_0 = ((uint16_t)1 << 0),
  gpioPin_1 = ((uint16_t)1 << 1),
  gpioPin_2 = ((uint16_t)1 << 2),
  gpioPin_3 = ((uint16_t)1 << 3),
  gpioPin_4 = ((uint16_t)1 << 4),
  gpioPin_5 = ((uint16_t)1 << 5),
  gpioPin_6 = ((uint16_t)1 << 6),
  gpioPin_7 = ((uint16_t)1 << 7),
  gpioPin_8 = ((uint16_t)1 << 8),
  gpioPin_9 = ((uint16_t)1 << 9),
  gpioPin_10 = ((uint16_t)1 << 10),
  gpioPin_11 = ((uint16_t)1 << 11),
  gpioPin_12 = ((uint16_t)1 << 12),
  gpioPin_13 = ((uint16_t)1 << 13),
  gpioPin_14 = ((uint16_t)1 << 14),
  gpioPin_15 = ((uint16_t) 1 << 15),
  gpioPin_All = ((uint16_t)0xFFFF),
} gpioPin_t;

typedef enum
{
  gpioMode_IN =0,
  gpioMode_OUT,
  gpioMode_AF,
  gpioMode_ANALOG,
}gpioMode_t;

typedef enum
{
  gpioPuPd_NOPULL,
  gpioPuPd_PULLUP,
  gpioPuPd_PULLDOWN,
} gpioPuPd_t;

typedef enum
{
  gpioType_PUSHPULL,
  gpioType_OPENDRAIN,
} gpioType_t;

typedef enum {
    gpioAF_0 = 0,
    gpioAF_1,
    gpioAF_2,
    gpioAF_3,
    gpioAF_4,
    gpioAF_5,
    gpioAF_6,
    gpioAF_7,
    gpioAF_8,
    gpioAF_9,
    gpioAF_10,
    gpioAF_11,
    gpioAF_12,
    gpioAF_13,
    gpioAF_14,
    gpioAF_15,
    gpioAF_None
}gpioAF;
/*!****************************************************************************
* User typedef
*/

/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/
#define GPIO_PIN_SET(port, pin)        (port->BSRR = (1 << pin))
#define GPIO_PIN_RESET(port, pin)      (port->BSRR = (1 << pin + 0x10))
#define GPIO_PIN_GET(port, pin)        (port->IDR & (1 << pin))
#define GPIO_PIN_TOGGLE(port, pin)     (port->ODR ^= (1 << pin))
/*!****************************************************************************
* Prototypes for the functions
*/
void gpioInit (GPIO_TypeDef *port, uint8_t  pinNum,  gpioMode_t mode, gpioPuPd_t PuPd, gpioType_t type, gpioAF afNum, uint8_t initState);
void gpioAfInit (GPIO_TypeDef *port, uint8_t pinNum, gpioAF afNum);
 
#endif //GPIO_H_
/***************** (C) COPYRIGHT ************** END OF FILE ******** ЭрикМарина ****/