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
#include "lcd_backlight.h"

/*!****************************************************************************
* Memory
*/
static pwmChannel_t pwmLcdBacklight;
/*!****************************************************************************
* Functions
*/

void lcdBacklight_init()
{
    pwmLcdBacklight.tim = TIM5;
    pwmLcdBacklight.channel = 4;
    pwm_channelInit(&pwmLcdBacklight, GPIOA, 3);
}
void lcdBacklight_bright(uint8_t bright)
{
    pwm_dutySet(&pwmLcdBacklight, bright);
}

 