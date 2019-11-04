#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "OS/mainTSK.h"
#include "OS/taskPriority.h"

void OS_init(void){

    xTaskCreate((TaskFunction_t)mainTSK, "mainTSK", 128, NULL, MAIN_TSK_PRIORITY, NULL);

    vTaskStartScheduler();  
}