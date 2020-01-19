#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "Regulators/regulatorSolder.h"
#include "hard/thermocouples.h"
#include "eSolder/eSolder.h"

void solderTempMeasureReady(void)
{
    
}

SemaphoreHandle_t tempMeasureReadySemaph = NULL, tempMeasureCompleteSemaph = NULL;
//TODO: may be using static allocation and call 'xSemaphoreCreateBinaryStatic' ?? 

// @retval BaseType_t init status 
static BaseType_t solderControlTskInit(void)
{
    tempMeasureReadySemaph = xSemaphoreCreateBinary();
    if (NULL == tempMeasureReadySemaph)
    {
        return pdFALSE;
    }
    
    tempMeasureCompleteSemaph = xSemaphoreCreateBinary();
    if (NULL == tempMeasureCompleteSemaph)
    {
        return pdFALSE;
    }

    max31856mud_init(&thermocoupleSolder);
    if (thermocoupleSolder.state != max31856State_OK)
    {
        return pdFALSE;
    }
    solderTempMeasureSetReadyCb(solderTempMeasureReady);

    return pdTRUE;
}

__task void solderControlTsk(void)
{
    if (pdTRUE == solderControlTskInit())
    {
        while(thermocoupleSolder.state == max31856State_OK)
        {
            solderTempMeasureRequest();
            
            if (pdTRUE != xSemaphoreTake(tempMeasureReadySemaph, ESOLDER_TEMP_MEASURE_INACTIVITY_MS))
            {
                // Bad line between mcu and max31856
                break;
            }
            ////
            //eSolder.solder.devParam.connected
            ////

            max31856mud_oneShot(&thermocoupleSolder);
            
            if (pdTRUE != xSemaphoreTake(tempMeasureCompleteSemaph, ESOLDER_TEMP_MEASURE_INACTIVITY_MS))
            {
                break;
            }

            eSolder.solder.tempReal = max31856mud_getLinearizedTemp(&thermocoupleSolder);
            eSolder.solder.coldJunctionTemp = max31856mud_getColdJunctionTemp(&thermocoupleSolder);
            
            if (eSolder.solder.devParam.enabled)
            {
                solderRun();
            }
            vTaskDelay(ESOLDER_TEMP_MEASURE_PERIOD_MS / portTICK_PERIOD_MS);
        }
    }    
    solderOff();
    //TODO: view error
    vTaskDelete(NULL);

}