#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "hard/lcd/ili9341.h"
#include "UI/UI.h"


__task void mainTsk(void) {

    UI_MainWindowRendering();
    ili9341_displayOn();


    while(1){
        
    }
}