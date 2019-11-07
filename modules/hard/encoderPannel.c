#include "hard/encoderPannel.h"

Encoder encoderPannel;


void EncoderPannelInit(void) {
    encoderPannel.gpioA = GPIOC;
    encoderPannel.pinA = 6;
    encoderPannel.pinA_AFnum = 3;
    encoderPannel.gpioB = GPIOC;
    encoderPannel.pinB = 7;
    encoderPannel.pinB_AFnum = 3;
    encoderPannel.tim = TIM8;
    encoderInit(&encoderPannel);
}