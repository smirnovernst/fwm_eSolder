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

#include "ili9341.h"
/*!****************************************************************************
* User define
*/

#define F_DISPLAY_SENDDATA    ili9341_WriteData_16 
#define F_DISPLAY_SETPIXEL    ili9341_SetPixel
#define F_DISPLAY_SETREGION   ili9341_SetRegion
#define lcd_Background        ili9341_DrawBackground

/*!****************************************************************************
* User enum
*/

typedef enum
{
    LCD_COLOR_WHITE   = 0xffff,
    LCD_COLOR_BLACK   = 0x0,
    LCD_COLOR_RED     = 0xf800,
    LCD_COLOR_YELLOW  = 0xffe0,
    LCD_COLOR_GREEN   = 0x07e0,
    LCD_COLOR_CYAN    = 0x7ff,
    LCD_COLOR_BLUE    = 0x001f,
    LCD_COLOR_GRAY    = 0x9cd3,
}lcd_color_t;
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
    lcd_color_t    color;
    lcd_color_t    background;
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

void    lcd_Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, lcd_color_t color);
int16_t lcd_Char(int16_t x, int16_t y, char c, lcdParam_t *param );
int16_t lcd_String(int16_t x, int16_t y, char *s, lcdParam_t *param);
void    lcd_Image(uint16_t x, uint16_t y,const tImage16 *image);
void    lcd_Rect(int16_t x, int16_t y, int16_t w, int16_t h, lcd_color_t color);
void    lcd_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, lcd_color_t color);
void    lcd_FastHLine(int16_t x, int16_t y, uint16_t w, lcd_color_t color);
void    lcd_FastVLine(int16_t x, int16_t y, uint16_t h, lcd_color_t color);
#endif //lcd_h



