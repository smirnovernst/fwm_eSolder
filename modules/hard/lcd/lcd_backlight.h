/*
*@File      lcd_backlight.h 
*@Author    EricMarina
*@Version   
*@Date      10.05.2017
*@Breif     
*/
#ifndef lcd_backlight_h
#define lcd_backlight_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"
#include "GPIO.h"
#include "pwm.h"
/*!****************************************************************************
* User define
*/

/*!****************************************************************************
* User enum
*/

/*!****************************************************************************
* User typedef
*/

/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/
 
/*!****************************************************************************
* Prototypes for the functions
*/
void lcdBacklight_init();
void lcdBacklight_bright(uint8_t bright);
#endif //lcd_backlight_h



