/*
*@File      mainTSK.c 
*@Author    EricMarina
*@Version   v0.2
*@Date      16.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "mainTSK.h"
#include "pwr.h"
#include "lcd_backlight.h"

#include "menuTSK.h"

//--dbg
#include "spi_f4.h"
#include <string.h>
#include <assert.h>
//--dbg
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/
#include "max31856mud.h"
__task void mainTSK(void)
{
    
    
    
    //spi_init();
    static int16_t JunctionTemp = 0;
    static int32_t LinearizedTemp = 0;
    static uint8_t CR0 = 0, CR1 = 0;
    
    gpioInit(GPIOB, 7, gpioMode_OUT, gpioPuPd_NOPULL, gpioType_PUSHPULL, 0, 1);
    max31856mud_t solderTemp;
    solderTemp.spi = &spi1;
    solderTemp.portCS = GPIOB;
    solderTemp.pinCS = 7;
    
    max31856mud_init(&solderTemp);
    assert(solderTemp.state == max31856State_OK);
    
    while(1)
    {
         JunctionTemp = max31856mud_getColdJunctionTemp(&solderTemp);
         LinearizedTemp = max31856mud_getLinearizedTemp(&solderTemp);
         //max31856mud_oneShot(&solderTemp);
         max31856mud_startConvMode(&solderTemp);
    }
    UI_WindowRendering();
    ili9341_displayOn;
    UI_Update(&stationState);
    lcdBacklight_bright(100);
    
    
    enSet(encSolder, 20, SOLDER_TEMPSET_MAX, TEMP_STEP, TEMP_BIGSTEP, enNONCIRC, enU16,  &stationState.solder.temperatueSet); 
    enWriteVal(&encSolder, stationState.solder.temperatueSet);  
    /*=========== Code ==========*/
    while(1)
    {
        GPIO_PIN_TOGLE(GPIOC, 0);
        /*=========== Key handlers ==========*/
        
        if(keyboardScan()) //if pressed at least one key
        {        
            //----------Enc_Solder AND Enc_dry Button----------
            if((keyboard.b_encSolder.pressType == pressType_LONG) && 
               (keyboard.b_encDry.pressType == pressType_LONG))
            {
                keyboard.b_encDry.pressType = pressType_NON;
                keyboard.b_encSolder.pressType = pressType_NON;
                xTaskCreate((TaskFunction_t)menuTSK,    "menuTSK",    128,   NULL, MAIN_TSK_PRIORITY,  NULL);
                vTaskDelete(NULL);
            }
            //----------Enc_Dry Button----------
            if(keyboard.b_encDry.pressType == pressType_SHORT)  
            {
                stationState.regulator_selected ^= 1;
                keyboard.b_encDry.pressType = pressType_NON;
            } 
            if(keyboard.b_encDry.pressType == pressType_LONG)  
            {
                stationState.dry.enable ^= 1;
                keyboard.b_encDry.pressType = pressType_NON;
            } 
            //----------Enc_Solder Button----------
            if(keyboard.b_encSolder.pressType == pressType_SHORT)  
            {
                if (stationState.solder.enable == enable_ON)
                {
                    stationState.solder.temperatueSet = 250; 
                }
                keyboard.b_encSolder.pressType = pressType_NON;
            } 
            if(keyboard.b_encSolder.pressType == pressType_LONG)  
            {
                stationState.solder.enable ^= 1;
                keyboard.b_encSolder.pressType = pressType_NON;
            } 
        }// end if keyboard.ANY
        /*=========== Encoders update ==========*/
        //------ Encdry select -------
        if (stationState.regulator_selected == DryRegulatorSelected_Set)
        {
            enSet(encDry, 20, DRY_TEMPSET_MAX, TEMP_STEP, TEMP_BIGSTEP, enNONCIRC, enU16,  &stationState.dry.temperatueSet); 
            enWriteVal(&encDry, stationState.dry.temperatueSet);
        }
        else
        {
            enSet(encDry, 0, 100, FLOW_STEP, FLOW_BIGSTEP, enNONCIRC, enU8,  &stationState.dryFlow); 
            enWriteVal(&encDry, stationState.dryFlow);
        }
        
        //------ Enable/disable encoders-------
        if (stationState.solder.enable == enable_ON)  
        {
            enEnable(encSolder);
        }
        else
        {
            enDisable(encSolder);
        }
        
        if (stationState.dry.enable == enable_ON)     
        {
            enEnable(encDry);
        }
        else
        {
            enDisable(encDry);
        }
        //----- encoders update
        enGet(&encSolder);
        enGet(&encDry);
        /*=========== UI update ==========*/
        UI_Update(&stationState);
        /*===========   ==========*/
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, (TickType_t)80/portTICK_PERIOD_MS); 
    }//end while
    
}
