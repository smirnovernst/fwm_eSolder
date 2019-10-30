/*
*@File      lcd.c 
*@Author    EricMarina
*@Version   0.1
*@Date      21.05.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "lcd.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/

/*!****************************************************************************
* @brief Drawing line
* @param
* @return  
*/
void lcd_Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, lcd_color_t color)
{
  
    //инициализация переменных
    int16_t deltaX = abs(x2 - x1);
    int16_t deltaY = abs(y2 - y1);
    int8_t signX = x1 < x2 ? 1 : -1;
    int8_t signY = y1 < y2 ? 1 : -1;
    int16_t error2;
    //инициализация ошибки 
    int16_t error = deltaX - deltaY;
    //вывод последней точки
    F_DISPLAY_SETPIXEL(x2, y2, color);
    //основной цикл
    while(x1 != x2 || y1 != y2)
    {
       
        F_DISPLAY_SETPIXEL(x1, y1, color);
       
        error2 = error * 2;
        //
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
 
}


/*!****************************************************************************
* @brief Put char 
* @param
* @return x coordinate the end of symbol
*/
int16_t lcd_Char(int16_t x, int16_t y, char c, lcdParam_t *param)
{   
 
    
    uint8_t width, height;
    
    c = c - param->font->chars[0].n;
    uint8_t c_width =param->font->chars[c].Image->w;
    
    uint8_t c_height = param->font->chars[c].Image->h;
   
    uint8_t *pdata = (uint8_t*)param->font->chars[c].Image->data;
    
    uint8_t  mask;
    uint8_t  bytesPerLine = ((c_width - 1)/8 + 1);
    uint8_t count=0;
    
    F_DISPLAY_SETREGION(x, x+c_width-1, y, y + c_height-1);

    for(height = 0; height < c_height; height++)
    {
        
        for(width = 0; width < bytesPerLine; width++)
        {
            count = c_width - (width * 8);
            if(count > 8)
            {
                count = 8;
            }            
            mask = 0x80;
           
            for(int j = 0; j < count; j++)
            {
                if((*pdata & mask) != 0)      
                {                   
                    F_DISPLAY_SENDDATA(param->background);
                }
                else                          
                {
                    
                    F_DISPLAY_SENDDATA(param->color);
                    
                }
                mask = mask >> 1;   
            }
            pdata++;
        }
    }
    return (x + param->font->chars[c].Image->w);
    

}
/*!****************************************************************************
* @brief Put string
* @param
* @return x coordinate the end of last symbol
*/
int16_t lcd_String(int16_t x, int16_t y, char *s, lcdParam_t *param)
{
    int16_t end_symbol;
    while(*s != 0)
    {
        
        end_symbol = lcd_Char(x, y, *s, param);
        x = end_symbol + param->distance;
        s++;
    }
    return end_symbol;
}

/*!****************************************************************************
* @brief 
* @param
* @return
*/
void lcd_Image(uint16_t x, uint16_t y,const tImage16 *image)
{
 
    uint16_t w = image->w;
    uint16_t h = image->h;
    uint16_t *data_pointer = (uint16_t*)image->data;
    
    F_DISPLAY_SETREGION(x, x + w - 1, y, y + h -1);    
    int i = w*h;
    while(i != 0)
    {
        F_DISPLAY_SENDDATA(*data_pointer);
        data_pointer++;
        i--;
    }
}
/*!****************************************************************************
* @brief 
* @param
* @return
*/
void lcd_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, lcd_color_t color)
{
    F_DISPLAY_SETREGION(x, x + w - 1, y, y + h -1);    
    for (uint32_t i = 0; i < w*h; i++)
    {
        F_DISPLAY_SENDDATA(color);
    }
}

/*!****************************************************************************
* @brief 
* @param
* @return
*/
void lcd_FastVLine(int16_t x, int16_t y, uint16_t h, lcd_color_t color)
{
    F_DISPLAY_SETREGION(x, x, y, y + h -1);  
    for (; h > 0; h--)
    {
        F_DISPLAY_SENDDATA(color);
    }
}

/*!****************************************************************************
* @brief Draw horizontal line
* @param
* @return
*/
void lcd_FastHLine(int16_t x, int16_t y, uint16_t w, lcd_color_t color)
{
    F_DISPLAY_SETREGION(x, x + w - 1, y, y);   
    for (; w > 0; w--)
    {
        F_DISPLAY_SENDDATA(color);
    }
}

/*!****************************************************************************
* @brief 
* @param
* @return
*/
void    lcd_Rect(int16_t x, int16_t y, int16_t w, int16_t h, lcd_color_t color)
{
    lcd_FastHLine(x, y, w, color);
    lcd_FastHLine(x, y+h, w, color);
    lcd_FastVLine(x, y, h, color);
    lcd_FastVLine(x+w, y, h, color);
}
