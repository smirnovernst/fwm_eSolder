/*!****************************************************************************
* @file    enco.c
* @author  Storozhenko Roman - D_EL,
           Smirnov Ernst 
* @version V2.3
* @date    13-05-2015, 05-11-2019
* @brief   Средства работы с энкодером
*/
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

    encoder->nowControlled = NULL;
    
    gpioInit( (encoderInit->gpioA, encoderInit->pinA, GPIO_Mode_InputWithPullUp);  //Вывод GPIOA.8 TIM1_CH1
    gpioInit()
    GPIO_Init(encoderInit->gpioB, encoderInit->pinB, GPIO_Mode_InputWithPullUp);  //Вывод GPIOA.9 TIM1_CH2



    //Настройка таймера
                             
    encoderInit->tim->CCMR1  = TIM_CCMR1_CC2S_0 | TIM_CCMR1_CC1S_0;         //Полярность сигнала для каждого входа
    encoderInit->tim->CCER   = TIM_CCER_CC1P | TIM_CCER_CC2P;
    encoderInit->tim->CCMR1 |= (TIM_CCMR1_IC2PSC_1 | TIM_CCMR1_IC1PSC_1);   //Capture is done once every 4 events
    encoderInit->tim->CCMR1 |= TIM_CCMR1_IC1F | TIM_CCMR1_IC2F;             //Input capture 1 filter fSAMPLING=fDTS/32, N=8
    encoderInit->tim->SMCR  = TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;              //Режим энкодера
    encoderInit->tim->ARR   = 0xFFFF;                                       //Значение, до которого считает
    encoderInit->tim->SMCR  |=  TIM_SMCR_ETPS_1;
    encoderInit->tim->CNT = (0xFFFF / 4) / 2;
    encoderInit->tim->CR1   = TIM_CR1_CEN;                                  //Включаем таймер
    
    encoder->tim = encoderInit->tim; 

}

/*!****************************************************************************
* @brief
*/
uint32_t enReadVal(EncoderControlled *controlled){
    if ((NULL == controlled) || (NULL == controlled->pVal)) return;

    if(encoder->memtype == enU8){
        return (*(uint8_t*)controlled->pval);
    }
    else if(encoder->memtype == enU16){
        return (*(uint16_t*)controlled->pval);
    }
    else if(encoder->memtype == enU32){
        return (*(uint32_t*)controlled->pval);
    }
    return 0xFFFFFFFF;
}

/*!****************************************************************************
* @brief
*/
void enWriteVal(EncoderControlled* controlled, int32_t val){
    if ((NULL == controlled)||(NULL == controlled->pVal)) return;

    if(controlled->memtype == enU8){
        (*(uint8_t*)controlled->pval) = val;
    }
    else if(encoder->memtype == enU16){
        (*(uint16_t*)controlled->pval) = val;
    }
    else if(encoder->memtype == enU32){
        (*(uint32_t*)controlled->pval) = val;
    }
}


/*!****************************************************************************
* @brief  
*/
enLimType_type encoderUpdate(Encoder* encoder, EncoderControlled *controlled) {
    if ((NULL == encoder) || (NULL == controlled)) return enNoLim;

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
            enWriteVal(encoder, controlled->min);
            return enNoLim;
        }
    }
    else {
        if (temp2 < controlled->min) {
            enWriteVal(encoder, controlled->min);
            return enLimUp;
        }
        if (temp2 > controlled->max) {
            enWriteVal(controlled, controlled->max);
            return enLimUp;
        }
    }
    enWriteVal(controlled, controlled->pVal+temp);
    return enNoLim;
}

/******************* (C) COPYRIGHT ***************** END OF FILE ********* D_EL *****/
