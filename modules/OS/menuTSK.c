/*
*@File      menuTSK.c 
*@Author    EricMarina
*@Version   
*@Date      08.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "menuTSK.h"

#include "mainTSK.h"

#include "lcd_backlight.h"
#include "keyboard.h"
#include "enco.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/

__task void menuTSK(void)
{
    /*=========== First initialisation ==========*/ 
    
    lcdBacklight_bright(100);
    UI_DrawMenu();

    //==========Menu init=========//
    UI_menu_t menu;
    menuEl_t menuElements[2];
    
    //--
    menuElements[0].name = "Autooff";
    menuElements[0].param=    &stationState.setting.autoOff;
    menuElements[0].min = 0;
    menuElements[0].max = 1;
    menuElements[0].memType = menuElMemType_BOOL;
    
    menuElements[1].name = "Beep enable";
    menuElements[1].param=    &stationState.setting.beep;
    menuElements[1].min = 0;
    menuElements[1].max = 1;
    menuElements[1].memType = menuElMemType_BOOL;
    
    /*
    menuElements[2].name = "testTest";
    menuElements[2].param=    &stationState.internalTemp;
    menuElements[2].min = 0;
    menuElements[2].max = 10;
    menuElements[2].memType = menuElMemType_U8;
    */
    
    menu.elements = menuElements;
    menu.elementsAmount = sizeof(menuElements)/sizeof(menuEl_t);
    menu.selectedEl = 0;
    
    
    
    //==========Encoder init=========//
    enSet(encDry, 0, menu.elementsAmount-1, 1, 1, enCIRC, enU8, &menu.selectedEl ); 
    
    enEnable(encDry);
    enEnable(encSolder);
    
    while(1)
    {
        UI_updateMenu(&menu);
        //========== =========//
        
        enGet(&encDry);
        enSet(encSolder, 
              menu.elements[menu.selectedEl].min, 
              menu.elements[menu.selectedEl].max, 
              1, 1, enNONCIRC, enU8, 
              menu.elements[menu.selectedEl].param ); 
        
        enGet(&encSolder);
        //==========Key handler=========//
        if(keyboardScan())
        {
            //----------Enc_Solder AND Enc_dry Button----------
            if((keyboard.b_encSolder.pressType == pressType_LONG) && 
               (keyboard.b_encDry.pressType == pressType_LONG))
            {
                keyboard.b_encDry.pressType = pressType_NON;
                keyboard.b_encSolder.pressType = pressType_NON;
                enDisable(encDry);
                enDisable(encSolder);
                lcdBacklight_bright(0);
                xTaskCreate((TaskFunction_t)mainTSK,    "mainTSK",    128,   NULL, MAIN_TSK_PRIORITY,  NULL);
                vTaskDelete(NULL);
            }
        }
        /*===========   ==========*/
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, (TickType_t)100/portTICK_PERIOD_MS); 
        
    }
}
