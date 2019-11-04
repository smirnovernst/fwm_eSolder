/*
*@File      ili9341.c 
*@Author    EricMarina
*@Version   0.1
*@Date      15.10.2016
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include <stdint.h>
#include "ili9341_communication.h"
#include "ili9341.h"


/*!****************************************************************************
* Memory
*/


ili9341_Orientation_t orientation;
/*!****************************************************************************
* Functions
*/



void ili9341_ColumnAddressSet(uint16_t column_start, uint16_t column_end);
void ili9341_PageAddressSet(uint16_t page_start, uint16_t page_end);

/*!****************************************************************************
* @brief 
* @param
* @return
*/
void ili9341_Init(void)
{

    ili9341_InitCommunication();
   
    /************************************************
    * Display init
    */  
    
    ili9341_Reset();        

    ili9341_WriteCommand(0xC0);	    //Power Control 1
    ili9341_WriteData(0x27);	 
    
    ili9341_WriteCommand(0xC1);	    //Power Control 2	
    ili9341_WriteData(0x21);

    ili9341_WriteCommand(0xC5);		//VCOM Control 1
    ili9341_WriteData(0x1A);	        
    ili9341_WriteData(0x4A);  	        
    
    ili9341_WriteCommand(0xC7);		//VCOM Control 2
    ili9341_WriteData(0x10);
    
    ili9341_SetOrientation(ILI9341_ORIENTATION_DEFAULT);
    orientation = ILI9341_ORIENTATION_DEFAULT;
    
    ili9341_WriteCommand(0x3A);	
    ili9341_WriteData(0x05); 
    
    ili9341_WriteCommand(0xB1);     //Frame Rate Control 
    ili9341_WriteData(0x00);
    ili9341_WriteData(0x18);
    
    ili9341_WriteCommand(0xB6);     //Display Function Control
    ili9341_WriteData(0x0A);
    ili9341_WriteData(0x82);
    ili9341_WriteData(0x27);
  
    ili9341_WriteCommand(0x11);
}


/*!****************************************************************************
* @brief Set column adress
*/
static inline void ili9341_ColumnAddressSet(uint16_t column_start, uint16_t column_end)
{
    ili9341_WriteCommand(0x2A);
    ili9341_WriteData_16(column_start);
    ili9341_WriteData_16(column_end);
}

/*!****************************************************************************
* @brief Set page adress
*/
static inline void ili9341_PageAddressSet(uint16_t page_start, uint16_t page_end)
{
    ili9341_WriteCommand(0x2B);
    ili9341_WriteData_16(page_start);
    ili9341_WriteData_16(page_end);
}

/*!****************************************************************************
* @brief Set pixel
*/
void ili9341_SetPixel(uint16_t x, uint16_t y, uint16_t color)
{
    
    ili9341_ColumnAddressSet(x,x);
    ili9341_PageAddressSet(y,y);
    ili9341_WriteCommand(0x2C);
    ili9341_WriteData_16(color);    
    
}

/*!****************************************************************************
* @brief Draw background
*/
void ili9341_DrawBackground(uint16_t color)
{
    if ((orientation == 0) || (orientation == 1))
    {
        ili9341_ColumnAddressSet(0, ILI9341_WIDTH);
        ili9341_PageAddressSet(0,ILI9341_HEIGHT);
    }
    if ((orientation == 2) || (orientation == 3))
    {
        ili9341_ColumnAddressSet(0, ILI9341_HEIGHT);
        ili9341_PageAddressSet(0,ILI9341_WIDTH);
    }  
    ili9341_WriteCommand(0x2C);
    for (int i=0; i < ILI9341_WIDTH*ILI9341_HEIGHT; i++)
    {
        ili9341_WriteData_16(color);
    }
}

/*!****************************************************************************
* @brief Set orientation
*/
void ili9341_SetOrientation(ili9341_Orientation_t orientation)
{
    ili9341_WriteCommand(0x36);
    switch(orientation)
    {
    case 0:
        ili9341_WriteData(0x48);
        break;
    case 1: 
        ili9341_WriteData(0x88);
        break;
    case 2:        
        ili9341_WriteData(0x28);
        break;
    case 3: 
        ili9341_WriteData(0xE8);
        break;
    default: break;
    }
    orientation = orientation;
}

/*!****************************************************************************
* @brief 
* @param
* @return
*/
void ili9341_SetRegion (int16_t x1, int16_t x2, int16_t y1, int16_t y2)
{
    ili9341_ColumnAddressSet(x1, x2);
    ili9341_PageAddressSet(y1, y2);
    ili9341_WriteCommand(0x2C);
}

inline void ili9341_Reset(void) {
    ili9341_WriteCommand(0x01);
}
inline void ili9341_displayOn(void){
    ili9341_WriteCommand(0x29);
}
inline void ili9341_displayOff(void){
    ili9341_WriteCommand(0x28);
}
inline void ili9341_displaySleepIn(void){
    ili9341_WriteCommand(0x10);
}
inline void ili9341_displayOut(void){
    ili9341_WriteCommand(0x11);
}