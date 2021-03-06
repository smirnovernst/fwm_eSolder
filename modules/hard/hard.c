#include "stm32f4xx.h"

#include "hard/lcd/ili9341.h"
#include "hard/keyboard.h"
#include "hard/lcd/lcd_backlight.h"
#include "hard/encoderPannel.h"
#include "Drivers/spi/spi1.h"

void hard_init(void){
    
    lcdBacklight_init();
    ili9341_Init();
    keyboardInit();
    EncoderPannelInit();
   
    Spi1_Init();
}