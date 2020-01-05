#include "hard/encoderPannel.h"

Encoder encoderPannel = {
    .gpioA = GPIOC,
    .pinA = 6,
    .pinA_AFnum = 3,
    .gpioB = GPIOC,  
    .pinB = 7,
    .pinB_AFnum = 3,
    .tim = TIM8
};


void EncoderPannelInit(void) {
    encoderInit(&encoderPannel);
}