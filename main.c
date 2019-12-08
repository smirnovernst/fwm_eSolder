#include "stm32f4xx.h"
#include "Drivers/mcu.h"
#include "hard/hard.h"

#include "hard/hard.h"
#include "OS/mainTSK.h"
#include "OS/taskPriority.h"
#include "Drivers/gpio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "OS/OS.h"



void initTsk(void){
    hard_init();
    xTaskCreate((TaskFunction_t)mainTsk, "mainTSK", 128, NULL, MAIN_TSK_PRIORITY, NULL);
    vTaskDelete( NULL );
}

void OS_init(void){
    xTaskCreate((TaskFunction_t)initTsk, "initTsk", 128, NULL, configMAX_PRIORITIES, NULL);

    vTaskStartScheduler();  
}


void main(void){
    SystemCoreClockUpdate();
    MCU_init();
    OS_init();
     
    while(1);
}