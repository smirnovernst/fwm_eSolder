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
#include <stddef.h>
#include "Drivers/button.h"
#include "Drivers/gpio.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/

void buttonInit(Button_t *button) {
    if (NULL == button) {
        return;
    }

    gpioInit(button->port, button->pin, gpioMode_IN, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, 0, 0);
    buttonClearPressed(button);
}

/*!****************************************************************************
* @brief 
* @param   
* @return -1 - param.error; 0 - inactive; 1 - active;
*/
int buttonScan(Button_t *button){
    if (NULL == button) {
        return -1;
    }

    if (GPIO_PIN_GET(button->port, button->pin)){
        if (button->pressCounter > BUTTON_LONG_PRESS_TRESHOLD) {
            //key pressed, holding, and NOT was released
            return 0;
        }
        button->pressCounter++;
        
        return 0;
    }
    else{
        if ((0 == button->pressCounter)||
            (button->pressCounter < BUTTON_SHOT_PRESS_TRESHOLD)) {
            return 0;
        }
        uint8_t pressCounter = button->pressCounter;
        button->pressCounter = 0;
        if (pressCounter > BUTTON_LONG_PRESS_TRESHOLD) {
            button->pressState = ButtonPressed_LONG;
            return 1;
        }
        else {
            button->pressState = ButtonPressed_SHORT;
            return 1;
        }
    }
}

void buttonClearPressed(Button_t* button) {
    if (NULL == button) {
        return;
    }

    button->pressCounter = 0;
    button->pressState = ButtonPressed_NO;
}

