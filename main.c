#include "stm32f4xx.h"
#include "Drivers/mcu.h"
#include "hard/hard.h"
#include "OS/OS.h"


void main(void){
    SystemCoreClockUpdate();
    MCU_init();
    hard_init();
    OS_init();

    while(1);
}