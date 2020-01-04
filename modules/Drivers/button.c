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
    gpioPuPd_t buttonPuPd = gpioPuPd_PULLDOWN;
    
    if (button->inverted >= ButtonInverted_YES){
        buttonPuPd = gpioPuPd_PULLUP;
    }

    gpioInit(button->port, button->pin, gpioMode_IN, buttonPuPd, gpioType_PUSHPULL, (gpioAF)0, 0);
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
    

    uint8_t releasedLevel = (button->inverted >= ButtonInverted_YES); 

    if (releasedLevel ^ (GPIO_PIN_GET(button->port, button->pin) > 0)){
        if (button->pressCounter > BUTTON_LONG_PRESS_TRESHOLD) {
            //key pressed, holding, and NOT was released
            return 0;
        }
        button->pressCounter++;
        if (button->pressCounter == BUTTON_LONG_PRESS_TRESHOLD)
        {
            button->pressState = ButtonPressed_LONG;
            return 1;
        }
        
        return 0;
    }
    else{
        button->pressState = ButtonPressed_NO;
        
        if (button->pressCounter < BUTTON_SHOT_PRESS_TRESHOLD) {
            return 0;
        }

        uint8_t pressCounter = button->pressCounter;
        button->pressCounter = 0;

        if (pressCounter < BUTTON_LONG_PRESS_TRESHOLD) {
            button->pressState = ButtonPressed_SHORT;
            return 1;
        }
        return 0;
    }
}

void buttonClearPressed(Button_t* button) {
    if (NULL == button) {
        return;
    }

    button->pressCounter = 0;
    button->pressState = ButtonPressed_NO;
}