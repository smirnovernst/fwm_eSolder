/*
*@File      lcd_backlight.c 
*@Author    EricMarina
*@Version   0.1
*@Date      10.05.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/

#include "Drivers/gpio.h"

/*!****************************************************************************
* Memory
*/

typedef struct {
    GPIO_TypeDef *port;
    uint8_t pinNum;
}lcdBacklight_t;

lcdBacklight_t backlight = {
    .port = GPIOB,
    .pinNum = 8
};
/*!****************************************************************************
* Functions
*/

void lcdBacklight_init()
{
    gpioInit(backlight.port, backlight.pinNum,gpioMode_OUT, gpioPuPd_NOPULL, gpioType_PUSHPULL, gpioAF_None, 0);
    GPIO_PIN_SET(backlight.port, backlight.pinNum);
}
void lcdBacklight_bright(uint8_t bright)
{
 
}

 