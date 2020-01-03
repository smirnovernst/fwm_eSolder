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
        .memtype = enU16
    }
};

mainTskEncoderSelected_t mainTskEncoderSelected = (mainTskEncoderSelected_t)0;
 
__task void mainTsk(void) {
    //TODO: need implemented reading from eeprom mainTskEncoderSelected

    UI_MainWindowRendering();
    
    ili9341_displayOn();
    keyboardClearAllPress();


    while(1){
    
        
        /*=========== Key handling ==========*/
        if (keyboardScan() > 0) {
            if ((ButtonPressed_LONG == keyboard.dryButton.pressState) &&
                (ButtonPressed_LONG == keyboard.solderButton.pressState)) {
                //--- GOTO MENU ---//
                keyboard.dryButton.pressState = ButtonPressed_NO;
                keyboard.solderButton.pressState = ButtonPressed_NO;
                BUTTON_MARK_PROCESSED(keyboard.dryButton);
                BUTTON_MARK_PROCESSED(keyboard.solderButton);
            }
            if (ButtonPressed_SHORT == keyboard.dryButton.pressState) {
                //--- enable/disable DRY ---//
                BUTTON_MARK_PROCESSED(keyboard.dryButton);
            }
            if (ButtonPressed_SHORT == keyboard.solderButton.pressState) {
                //--- enable/disable SOLDER ---//
                BUTTON_MARK_PROCESSED(keyboard.solderButton);
            }
            if (ButtonPressed_SHORT == keyboard.encoderButton.pressState) {
                //--- switching selected for encoder ---//
                mainTskEncoderSelected++;
                if (mainTskEncoderSelected >= mainTskEncoderSelected_END) {
                    mainTskEncoderSelected = (mainTskEncoderSelected_t)0;
                }
                BUTTON_MARK_PROCESSED(keyboard.encoderButton);
            }
        }
        /*=========== Encoder update ==========*/
        encoderUpdate(&encoderPannel, &encControlledMain[mainTskEncoderSelected]);
        


    }
}

mainTskEncoderSelected_t mainTsk_GetEncoderSelected(void)
{
    return mainTskEncoderSelected;
}