#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "mainTsk.h"

#include "hard/lcd/ili9341.h"
#include "hard/keyboard.h"
#include "hard/encoderPannel.h"
#include "UI/UI.h"
#include "eSolder/eSolder.h"



EncoderControlled encControlledMain[mainTskEncoderSelected_END] = {
    {
        // EncoderControlled_SOLDER_TEMP
        .pVal = &eSolder.solder.tempSet,
        .min = ESOLDER_TEMP_SET_MIN,
        .max = ESOLDER_TEMP_SET_MAX,
        .step = ESOLDER_TEMP_SET_STEP,
        .bigStep = ESOLDER_TEMP_SET_BIGSTEP,
        .mode = enNONCIRC,
        .memtype = enU16
    },
    {
        // EncoderControlled_DRY_TEMP
        .pVal = &eSolder.dry.tempSet, 
        .min = ESOLDER_TEMP_SET_MIN,
        .max = ESOLDER_TEMP_SET_MAX,
        .step = ESOLDER_TEMP_SET_STEP,
        .bigStep = ESOLDER_TEMP_SET_BIGSTEP,
        .mode = enNONCIRC,
        .memtype = enU16
    },
    {
        // EncoderControlled_DRY_FLOW
        .pVal =  &eSolder.dry.flowSet, 
        .min = ESOLDER_FLOW_SET_MIN,
        .max = ESOLDER_FLOW_SET_MAX,
        .step = ESOLDER_FLOW_SET_STEP,
        .bigStep = ESOLDER_FLOW_SET_BIGSTEP,
        .mode = enNONCIRC,
        .memtype = enU8
    }
};

mainTskEncoderSelected_t mainTskEncoderSelected = (mainTskEncoderSelected_t)0;
 
__task void mainTsk(void) {
    //TODO: need implemented reading from eeprom mainTskEncoderSelected

    UI_MainWindowRendering();
    
    ili9341_displayOn();
    keyboardClearAllPress();


    while(1){
        UI_MainWindowUpdate();
        
        /*=========== Key handling ==========*/
        if (keyboardScan() > 0) {
            if ((ButtonPressed_LONG == keyboard.buttons[KeyboardButton_DRY].pressState) &&
                (ButtonPressed_LONG == keyboard.buttons[KeyboardButton_SOLDER].pressState)) {
                //--- GOTO MENU ---//
                BUTTON_MARK_LONG_PRESS_PROCESSED(keyboard.buttons[KeyboardButton_DRY]);
                BUTTON_MARK_LONG_PRESS_PROCESSED(keyboard.buttons[KeyboardButton_SOLDER]);
            }
            if (ButtonPressed_SHORT == keyboard.buttons[KeyboardButton_DRY].pressState) {
                //--- enable/disable DRY ---//
                
            }
            if (ButtonPressed_SHORT == keyboard.buttons[KeyboardButton_SOLDER].pressState) {
                //--- enable/disable SOLDER ---//
                
            }
            if (ButtonPressed_SHORT == keyboard.buttons[KeyboardButton_ENCODER].pressState) {
                //--- switching selected for encoder ---//
                mainTskEncoderSelected++;
                if (mainTskEncoderSelected >= mainTskEncoderSelected_END) {
                    mainTskEncoderSelected = (mainTskEncoderSelected_t)0;
                }
                
            }
        }
        /*=========== Encoder update ==========*/
        encoderUpdate(&encoderPannel, &encControlledMain[mainTskEncoderSelected]);
        



    }
    
    vTaskDelay(500 / portTICK_PERIOD_MS);
    
}

mainTskEncoderSelected_t mainTsk_GetEncoderSelected(void)
{
    return mainTskEncoderSelected;
}