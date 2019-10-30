/*
*@File      systemTSK.c 
*@Author    EricMarina
*@Version   
*@Date      01.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "systemTSK.h"
#include "OSInit.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* prototypes
*/
static void errorChecker (deviceParametrs_t *device);
/*!****************************************************************************
* Functions
*/

__task void systemTSK(void)
{

    while(1)
    {
        uint8_t i=0;
        i++;
    }
    while(1)
    {
        
        /************************SOLDER*********************/
        if(stationState.solder.enable)
        {
             //--------- En/Disable regulator--------- 
            if (stationState.solder.status != deviceStatus_Fail)
            {
                 //regulator_solderON; //@TODO: need release 
            }
            else
            {
                #if (DBG_FAILOUTOFF_DISABLE == 0)
                    regulator_solderOFF;
                #endif
            }
        }
        else
        {   
             //--------- Disable regulator-------- 
            regulator_solderOFF();
        }
        
        
        
        
        /*************************DRY*************************/
        if (stationState.dry.enable == enable_ON)
        {
              //--------- En/Disable regulator-------- 
            if (stationState.dry.status != deviceStatus_Fail)
            {
                //regulator_dryON; //@TODO: need release 
            }
            else
            {
                #if (DBG_FAILOUTOFF_DISABLE == 0)
                    regulator_dryOFF;
                #endif
            }
         //--------- Dry reed check -------- 
        
         //--------- PWM motor dry update -------- 
            dryFan_setFlow(stationState.dryFlow);  
        }
        
        else
        {
             //---------Disable regulator -------- 
             regulator_dryOFF();
             
            //---------PWM motor dry off --------
             dryFan_setFlow(0);
        }
           
        
             
        /*=========== Status check ==========*/
        if (stationState.dry.status == deviceStatus_Fail)
        {
            errorChecker(&stationState.dry);
        }
        if (stationState.solder.status == deviceStatus_Fail)
        {
            errorChecker(&stationState.solder);
        }
        
        //------------------------------------
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, (TickType_t)10/portTICK_PERIOD_MS); 
    }
}

void errorChecker (deviceParametrs_t *device)
{
    if(device->connection == 0) return;
   
    //-------------
    device->status = deviceStatus_Ok;
    return;
}
