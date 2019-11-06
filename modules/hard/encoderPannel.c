#include "hard/encoderPannel.h"

Encoder encoderPannel;

void EncoderPannelInit(void) {
    encoderPannel.gpioA = ;
    encoderPannel.gpioB = ;
    encoderPannel.tim = ;
    encoderInit(&encoderPannel);
}