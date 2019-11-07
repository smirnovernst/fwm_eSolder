/*
*@File      ili9341.h 
*@Author    EricMarina
*@Version   0.1
*@Date      15.10.2016
*@Breif     
*/
#ifndef ili9341_h
#define ili9341_h
/*!****************************************************************************
* Include
*/


#include "Drivers/gpio.h"

/*!****************************************************************************
* User define
*/

#define ILI9341_ORIENTATION_DEFAULT     ILI9341_LANDSCAPE_2
#define ILI9341_BACKGROUND_DEFAULT      LCD_COLOR_565_BLACK

#define ILI9341_WIDTH   240
#define ILI9341_HEIGHT  320

//Colors
#define ILI9341_COLORFORMAT     RGB565

/*!****************************************************************************
* User enum
*/
typedef enum
{
   PORTRAIT_1 = 0,
   PORTRAIT_2 = 1,
   ILI9341_LANDSCAPE_1 = 2,
   ILI9341_LANDSCAPE_2 = 3 
}ili9341_Orientation_t;
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


//control
void ili9341_Init(void);
void ili9341_DrawBackground(uint16_t color);
void ili9341_SetOrientation(ili9341_Orientation_t orientation);
void ili9341_Reset(void);
void ili9341_displayOn(void);
void ili9341_displayOff(void);
void ili9341_displaySleepIn(void);
void ili9341_displayOut(void);

//graph
void ili9341_SetPixel(uint16_t x, uint16_t y, uint16_t color);
void ili9341_SetRegion (int16_t x1, int16_t x2, int16_t y1, int16_t y2);



#endif //ili9341_h
