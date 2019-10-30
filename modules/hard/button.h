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
#include "global_inc.h"
#include "GPIO.h"
/*!****************************************************************************
* User define
*/
#define BUTTON_LONG_PRESS_TRESHOLD     5
/*!****************************************************************************
* User enum
*/
typedef enum
{
    pressType_NON,
    pressType_SHORT,
    pressType_LONG,
}pressType_t;

/*!****************************************************************************
* User typedef
*/

// if val pressCounter - (-1) - button holding in press state
//                       (0)  - button released
//                       (>0) - button  pressed
typedef struct
{  
    GPIO_TypeDef    *port;
    uint8_t         pin;
    int8_t          pressCounter; 
    pressType_t     pressType;
}button_t;


/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
uint8_t buttonScan(button_t *button);
//@TODO: need release for stm32f4
//inline void buttonInit(button_t *button) { GPIO_Init(button->port, button->pin, GPIO_Mode_InputWithPullDown);}
inline void buttonInit(button_t *button){}


#endif //button_h



