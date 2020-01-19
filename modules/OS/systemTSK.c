#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "hard/thermocouples.h"
#include "eSolder/eSolder.h"


void ThermocoupleInterrogate(Device_t *pDev, max31856State_t *pThermocouple, uint16_t *pTemp, uint16_t *pColdJunction)
{
    if (pThermocouple->state == max31856State_OK)
    {
        max31856mud_getLinearizedTemp(&pThermocouple);
    }
}



__task void systemTsk(void)
{

    
    if (thermocoupleDry.state != max31856State_OK)
    {
        // TODO: view error!
        
    }
    max31856mud_init(&thermocoupleSolder);

    while(1)
    {
        if (thermocoupleDry.state == max31856State_OK)
        {
            
        }
    }
}