/*
*@File      lcd.h 
*@Author    EricMarina
*@Version   0.1
*@Date      21.05.2017
*@Breif     
*/
#ifndef lcd_h
#define lcd_h
/*!****************************************************************************
* Include
*/
#include <stdint.h>

/*!****************************************************************************
* User define
*/



/*!****************************************************************************
* User enum
*/

typedef enum{
    LCD_COLOR_565_WHITE   = 0xffff,
    LCD_COLOR_565_BLACK   = 0x0,
    LCD_COLOR_565_RED     = 0xf800,
    LCD_COLOR_565_YELLOW  = 0xffe0,
    LCD_COLOR_565_GREEN   = 0x07e0,
    LCD_COLOR_565_CYAN    = 0x7ff,
    LCD_COLOR_565_BLUE    = 0x001f,
    LCD_COLOR_565_GRAY    = 0x9cd3,
}lcdColorRgb565;
/*!****************************************************************************
* User typedef
*/

typedef struct
{
    const uint8_t     *data;
    uint8_t     w;
    uint8_t     h;
}tImage;

typedef struct
{
    const uint8_t n;
    const tImage  *Image;
}tChar;

typedef struct
{
    int length;
    const tChar *chars;
}tFont;

typedef struct
{
    const uint16_t     *data;
    uint16_t     w;
    uint16_t     h;
}tImage16;

typedef struct
{  
    const tFont *font;
    uint8_t     distance;
    lcdColorRgb565    color;
    lcdColorRgb565    background;
}lcdParam_t;
/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/

void    lcd_Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, lcdColorRgb565 color);
int16_t lcd_Char(int16_t x, int16_t y, char c, lcdParam_t *param );
int16_t lcd_String(int16_t x, int16_t y, char *s, lcdParam_t *param);
void    lcd_Image(uint16_t x, uint16_t y,const tImage16 *image);
void    lcd_Rect(int16_t x, int16_t y, int16_t w, int16_t h, lcdColorRgb565 color);
void    lcd_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, lcdColorRgb565 color);
void    lcd_FastHLine(int16_t x, int16_t y, uint16_t w, lcdColorRgb565 color);
void    lcd_FastVLine(int16_t x, int16_t y, uint16_t h, lcdColorRgb565 color);
#endif //lcd_h



