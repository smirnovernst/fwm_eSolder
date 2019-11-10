#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "hard/hard.h"
#include "OS/mainTSK.h"
#include "OS/taskPriority.h"
void initTsk(void){
    hard_init();
    
    xTaskCreate((TaskFunction_t)mainTsk, "mainTSK", 128, NULL, MAIN_TSK_PRIORITY, NULL);
    vTaskDelete( NULL );
}

void OS_init(void){

    xTaskCreate((TaskFunction_t)initTsk, "initTsk", 128, NULL, configMAX_PRIORITIES, NULL);

    vTaskStartScheduler();  
}