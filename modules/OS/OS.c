#include "hard/hard.h"
#include "OS/mainTSK.h"
#include "OS/taskPriority.h"
#include "Drivers/gpio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

void dbgTSK(void){
    gpioInit(GPIOC, 0, gpioMode_OUT,gpioPuPd_NOPULL,gpioType_PUSHPULL, 0, 0);
    while(1){
        GPIO_PIN_SET(GPIOC, 0);
        GPIO_PIN_RESET(GPIOC, 0);
    }
}

void initTsk(void){
    hard_init();
    xTaskCreate((TaskFunction_t)mainTsk, "mainTSK", 128, NULL, MAIN_TSK_PRIORITY, NULL);
    xTaskCreate((TaskFunction_t)dbgTSK, "dbgTSK", 128, NULL, MAIN_TSK_PRIORITY, NULL);
    vTaskDelete( NULL );
}

void OS_init(void){

    xTaskCreate((TaskFunction_t)initTsk, "initTsk", 128, NULL, configMAX_PRIORITIES, NULL);

    vTaskStartScheduler();  
}