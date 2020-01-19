#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "hard/thermocouples.h"
#include "eSolder/eSolder.h"




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