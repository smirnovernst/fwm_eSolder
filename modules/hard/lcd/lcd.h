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
#include "hard/lcd/lcd_colors.h"

/*!****************************************************************************
* User define
*/

/*!****************************************************************************
* User enum
*/

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
    int         length;
    const tChar *chars;
}tFont;

typedef struct
{
    const uint16_t  *data;
    uint16_t        w;
    uint16_t        h;
}tImage16;

typedef struct
{  
    const tFont *font;
    uint8_t     distance;
    uint16_t    color;
    uint16_t    background;
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

void    lcd_Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
int16_t lcd_Char(int16_t x, int16_t y, char c,const lcdParam_t *param );
int16_t lcd_String(int16_t x, int16_t y, char *s,const lcdParam_t *param);
void    lcd_Image(uint16_t x, uint16_t y,const tImage16 *image);
void    lcd_Rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void    lcd_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void    lcd_FastHLine(int16_t x, int16_t y, uint16_t w, uint16_t color);
void    lcd_FastVLine(int16_t x, int16_t y, uint16_t h, uint16_t color);
void    lcd_DrawBackground(uint16_t color);
#endif //lcd_h



