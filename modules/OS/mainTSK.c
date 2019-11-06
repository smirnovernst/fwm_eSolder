#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "hard/encoderPannel.h"

__task void mainTsk(void) {


    UI_WindowRendering();
    ili9341_displayOn();

    while(1){

    }
}