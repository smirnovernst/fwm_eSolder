#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"



__task void mainTsk(void) {


    UI_WindowRendering();
    ili9341_displayOn();

    while(1){

    }
}