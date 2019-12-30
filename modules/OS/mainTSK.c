#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "hard/lcd/ili9341.h"
#include "hard/keyboard.h"
#include "hard/encoderPannel.h"
#include "UI/UI.h"
#include "station/eSolderConstants.h"

typedef enum {
    EncoderControlled_SOLDER_TEMP = 0,
    EncoderControlled_DRY_TEMP,
    EncoderControlled_DRY_FLOW,
    EncoderControlled_END,
}EncoderControlledMain;
EncoderControlled encControlledMain[EncoderControlled_END] = {
    {
        // EncoderControlled_SOLDER_TEMP
        .pVal = NULL, //TODO; add
        .min = ESOLDER_TEMP_SET_MIN,
        .max = ESOLDER_TEMP_SET_MAX,
        .step = ESOLDER_TEMP_SET_STEP,
        .bigStep = ESOLDER_TEMP_SET_BIGSTEP,
        .mode = enNONCIRC,
        .memtype = enU16
    },
     {
         // EncoderControlled_DRY_TEMP
         .pVal = NULL, //TODO; add
         .min = ESOLDER_TEMP_SET_MIN,
         .max = ESOLDER_TEMP_SET_MAX,
         .step = ESOLDER_TEMP_SET_STEP,
         .bigStep = ESOLDER_TEMP_SET_BIGSTEP,
         .mode = enNONCIRC,
         .memtype = enU16
     },
      {
          // EncoderControlled_DRY_FLOW
          .pVal = NULL, //TODO; add
          .min = ESOLDER_TEMP_SET_MIN,
          .max = ESOLDER_TEMP_SET_MAX,
          .step = ESOLDER_TEMP_SET_STEP,
          .bigStep = ESOLDER_TEMP_SET_BIGSTEP,
          .mode = enNONCIRC,
          .memtype = enU16
      },

};

__task void mainTsk(void) {

    EncoderControlled *encoderNowControlled = EncoderControlled_SOLDER_TEMP;
    //TODO: Need release saving/reading from eeprom

    UI_MainWindowRendering();
    
    ili9341_displayOn();
    keyboardClearAllPress();


    while(1){
  UI_MainWindowRendering();
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
                encoderNowControlled++;
                /*if (encoderNowControlled >= ) {
                    encoderNowControlled = 
                }*/
                BUTTON_MARK_PROCESSED(keyboard.encoderButton);
            }
        }
        /*=========== Encoder update ==========*/
        encoderUpdate(&encoderPannel, encoderNowControlled);
        


    }
}