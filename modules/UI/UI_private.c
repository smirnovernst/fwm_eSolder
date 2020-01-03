/*
*@File      UI.c 
*@Author    EricMarina
*@Version   0.1
*@Date      18.11.2016
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "UI_private.h"

/*!****************************************************************************
* Memory
*/
 const UI_t ui = {
     .colors = {
        .background = LCD_COLOR_BLACK,
        .mainColor = LCD_COLOR_WHITE,
        .selectColor = LCD_COLOR_CYAN,
        .disconnectedColor = LCD_COLOR_GRAY
     },
     .fonts = {
         .mainFont = &Arial,
         .bigDigitFont = &DS_Digital,
         .smallDigitFont = &DS_Digital_Small
     }  
};
