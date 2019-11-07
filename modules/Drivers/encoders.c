/*!****************************************************************************
* @file    enco.c
* @author  Storozhenko Roman - D_EL,
           Smirnov Ernst 
* @version V2.3
* @date    13-05-2015, 05-11-2019
* @brief   Средства работы с энкодером
*/
#include <stddef.h>
#include "stm32f4xx.h"
#include "Drivers/encoders.h"
#include "Drivers/gpio.h"

/******************************************************************************
* MEMORY
*/

/******************************************************************************
* @brief  Настройка периферии МК для работы с инкрементальным энкодером
*/
void encoderInit(Encoder* encoder){
    if (NULL == encoder) return;

    
    gpioInit(encoder->gpioA, encoder->pinA, gpioMode_IN, gpioPuPd_PULLUP, gpioType_PUSHPULL, (gpioAF)encoder->pinA_AFnum, 1);
    gpioInit(encoder->gpioB, encoder->pinB, gpioMode_IN, gpioPuPd_PULLUP, gpioType_PUSHPULL, (gpioAF)encoder->pinB_AFnum, 1);
    
    //Настройка таймера               
    encoder->tim->CCMR1  = TIM_CCMR1_CC2S_0 | TIM_CCMR1_CC1S_0;         //Полярность сигнала для каждого входа
    encoder->tim->CCER   = TIM_CCER_CC1P | TIM_CCER_CC2P;
    encoder->tim->CCMR1 |= (TIM_CCMR1_IC2PSC_1 | TIM_CCMR1_IC1PSC_1);   //Capture is done once every 4 events
    encoder->tim->CCMR1 |= TIM_CCMR1_IC1F | TIM_CCMR1_IC2F;             //Input capture 1 filter fSAMPLING=fDTS/32, N=8
    encoder->tim->SMCR  = TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;              //Режим энкодера
    encoder->tim->ARR   = 0xFFFF;                                       //Значение, до которого считает
    encoder->tim->SMCR  |=  TIM_SMCR_ETPS_1;
    encoder->tim->CNT = (0xFFFF / 4) / 2;
    encoder->tim->CR1   = TIM_CR1_CEN;                                  //Включаем таймер
    
    encoder->nowControlled = NULL;
}

/*!****************************************************************************
* @brief
*/
uint32_t enReadVal(EncoderControlled *controlled){
    if ((NULL == controlled) || (NULL == controlled->pVal)) {
        return 0;
    }

    if(controlled->memtype == enU8){
        return (*(uint8_t*)controlled->pVal);
    }
    else if(controlled->memtype == enU16){
        return (*(uint16_t*)controlled->pVal);
    }
    else if(controlled->memtype == enU32){
        return (*(uint32_t*)controlled->pVal);
    }
    return 0xFFFFFFFF;
}

/*!****************************************************************************
* @brief
*/
void enWriteVal(EncoderControlled* controlled, int32_t val){
    if ((NULL == controlled)||(NULL == controlled->pVal)) return;

    if(controlled->memtype == enU8){
        (*(uint8_t*)controlled->pVal) = val;
    }
    else if(controlled->memtype == enU16){
        (*(uint16_t*)controlled->pVal) = val;
    }
    else if(controlled->memtype == enU32){
        (*(uint32_t*)controlled->pVal) = val;
    }
}


/*!****************************************************************************
* @brief  
*/
enLimType_type encoderUpdate(Encoder* encoder, EncoderControlled *controlled) {
    if ((NULL == encoder) || (NULL == controlled)) {
        return enNoLim;
    }

    if (encoder->nowControlled != controlled) {
        encoder->nowControlled = controlled;
        encoder->tim->CNT = (0xFFFF / 4) / 2;
        return enNoChanged;
    }

    int32_t             temp;
    int64_t             temp2;

    temp = encoder->tim->CNT - (0xFFFF / 4) / 2;
    encoder->tim->CNT = (0xFFFF / 4) / 2;
    if (temp > 0) {
        temp = (temp + 2) / 4;
    }
    else {
        temp = (temp - 2) / 4;
    }
    /*
      //Ускоритель
      if(temp > 2){
          temp *= 5;
      }
      if(temp < -2){
          temp *= 5;
      }
      */
    if (0 == temp) {
        return enNoChanged;
    }
    temp = temp * controlled->step; //Шаг

    temp2 = enReadVal(controlled);
    temp2 += temp;

    if (controlled->mode == enCIRC) {
        if (temp2 < controlled->min) {
            enWriteVal(controlled, controlled->max);
            return enNoLim;
        }
        if (temp2 > controlled->max) {
            enWriteVal(controlled, controlled->min);
            return enNoLim;
        }
    }
    else {
        if (temp2 < controlled->min) {
            enWriteVal(controlled, controlled->min);
            return enLimUp;
        }
        if (temp2 > controlled->max) {
            enWriteVal(controlled, controlled->max);
            return enLimUp;
        }
    }

    if(controlled->memtype == enU8){
        (*(uint8_t*)controlled->pVal) = (*(uint8_t*)controlled->pVal)+temp;
    }
    else if(controlled->memtype == enU16){
        (*(uint16_t*)controlled->pVal) = (*(uint16_t*)controlled->pVal)+temp;
    }
    else if(controlled->memtype == enU32){
        (*(uint32_t*)controlled->pVal) = (*(uint32_t*)controlled->pVal)+temp;
    }
    return enNoLim;
}

/******************* (C) COPYRIGHT ***************** END OF FILE ********* D_EL *****/
