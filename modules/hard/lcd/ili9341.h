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
#include "stdint.h"
#include <stdlib.h>
#include "global_inc.h"
#include "GPIO.h"
#include "spi.h"
/*!****************************************************************************
* User define
*/
//settings
#define ILI9341_CSX_PIN    15
#define ILI9341_CSX_PORT   GPIOA
#define ILI9341_DCX_PIN    2
#define ILI9341_DCX_PORT   GPIOD

#define ILI9341_SPI        SPI1


#define ILI9341_ORIENTATION_DEFAULT     ILI9341_LANDSCAPE_2
#define ILI9341_BACKGROUND_DEFAULT      LCD_COLOR_GREEN

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
#define ili9341_sleepIn ili9341_WriteCommand(0x10)
#define ili9341_sleepOut ili9341_WriteCommand(0x11)
#define ili9341_displayOff ili9341_WriteCommand(0x28)
#define ili9341_displayOn ili9341_WriteCommand(0x29)
/*!****************************************************************************
* Prototypes for the functions
*/



//private
void ili9341_WriteData(uint8_t Data);
void ili9341_WriteData_16(uint16_t Data);
void ili9341_WriteCommand(uint8_t command);
void ili9341_ReadData(uint8_t* response, int count);
void ili9341_ColumnAddressSet(uint16_t column_start, uint16_t column_end);
void ili9341_PageAddressSet(uint16_t page_start, uint16_t page_end);


//control
void ili9341_Init(void);
void ili9341_DrawBackground(uint16_t color);
void ili9341_SetOrientation(ili9341_Orientation_t orientation);
inline void ili9341_Reset(void) {ili9341_WriteCommand(0x01);}

//graph
void ili9341_SetPixel(uint16_t x, uint16_t y, uint16_t color);
void ili9341_SetRegion (int16_t x1, int16_t x2, int16_t y1, int16_t y2);



#endif //ili9341_h
