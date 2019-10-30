/*
*@File      button.c 
*@Author    EricMarina
*@Version   
*@Date      16.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "button.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/


/*!****************************************************************************
* @brief 
* @param   
* @return 1 - if button pressed; 0 - not was pressed;
*/
uint8_t buttonScan(button_t *button)
{   
    if (GPIO_PIN_GET(button->port, button->pin))
    {
        if (button->pressCounter < 0) return 0; //key pressed, holding, and NOT was released
        
        button->pressCounter++;
        
        if (button->pressCounter > BUTTON_LONG_PRESS_TRESHOLD)
        {
            //key pressed and holding(LONG PRESS)
            button->pressCounter = -1;
            button->pressType = pressType_LONG;
            return 1;
        }
    }
    else
    {
        if ( button->pressCounter > 0 )
        {
            //key was pressed and released (SHORT PRESS)
            button->pressCounter = 0;
            button->pressType = pressType_SHORT;
            return 1;
        }
        button->pressCounter = 0;
    }
    return 0;
}

