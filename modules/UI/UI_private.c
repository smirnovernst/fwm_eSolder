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
        .disableColor = LCD_COLOR_GRAY
     }
    
};

void UI_prvt_drawCross(uint16_t x, uint16_t y, uint16_t len)
{
    lcd_Line(x, y, x+len, y+len, UI_CROSS_COLOR);
    lcd_Line(x+len, y, x, y+len, UI_CROSS_COLOR);
}