#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

void OS_init(void){
    vTaskStartScheduler();  
    
}