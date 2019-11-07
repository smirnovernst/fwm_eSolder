#include "stm32f4xx.h"

#include "hard/lcd/ili9341.h"
#include "hard/keyboard.h"

void hard_init(void){
    ili9341_Init();
    keyboardInit();


}