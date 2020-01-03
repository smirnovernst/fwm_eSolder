/*
*@File      button.h 
*@Author    EricMarina
*@Version   
*@Date      16.07.2017
*@Breif     
*/
#ifndef button_h
#define button_h
/*!****************************************************************************
* Include
*/
#include "stm32f4xx.h"

/*!****************************************************************************
* User define
*/
#define BUTTON_LONG_PRESS_TRESHOLD     5
#define BUTTON_SHOT_PRESS_TRESHOLD     1
/*!****************************************************************************
* User enum
*/
typedef enum
{
    ButtonPressed_NO = 0,
    ButtonPressed_SHORT,
    ButtonPressed_LONG,
    ButtonPressed_NONE //invalid state
}ButtonPressed_t;
typedef enum
{
    ButtonInverted_NO = 0,
    ButtonInverted_YES
}ButtonInverted_t;

/*!****************************************************************************
* User typedef
*/


typedef struct
{  
    GPIO_TypeDef        *port;
    uint8_t             pin;
    ButtonInverted_t    inverted;
    uint8_t             pressCounter; 
    ButtonPressed_t     pressState;
}Button_t;


/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/
#define BUTTON_MARK_PROCESSED(button) { button.pressState = ButtonPressed_NO; }
/*!****************************************************************************
* Prototypes for the functions
*/
int buttonScan(Button_t* button);
void buttonClearPressed(Button_t* button);
void buttonInit(Button_t *button);


#endif //button_h



