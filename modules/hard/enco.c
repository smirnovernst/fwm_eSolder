/*!****************************************************************************
* @file    enco.c
* @author  Storozhenko Roman - D_EL
* @version V2.3
* @date    13-05-2015 
* @brief   Средства работы с энкодером
*/
#include "enco.h"

/******************************************************************************
* MEMORY
*/

encoder_t encSolder, encDry;
/******************************************************************************
* @brief  Настройка периферии МК для работы с инкрементальным энкодером
*/
void encoderInit(encoder_t *encoder, encoderInit_t *encoderInit){
#if 0
    //@TODO: Need release for stm32f4
    gpioInit( (encoderInit->gpioA, encoderInit->pinA, GPIO_Mode_InputWithPullUp);  //Вывод GPIOA.8 TIM1_CH1
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
#endif
}

/*!****************************************************************************
* @brief
*/
uint32_t enReadVal(encoder_t *encoder){
    if(encoder->memtype == enU8){
        return (*(uint8_t*)encoder->pval);
    }
    else if(encoder->memtype == enU16){
        return (*(uint16_t*)encoder->pval);
    }
    else if(encoder->memtype == enU32){
        return (*(uint32_t*)encoder->pval);
    }
    return 0xFFFFFFFF;
}

/*!****************************************************************************
* @brief
*/
void enWriteVal(encoder_t *encoder, int32_t val){
    if(encoder->memtype == enU8){
        (*(uint8_t*)encoder->pval) = val;
    }
    else if(encoder->memtype == enU16){
        (*(uint16_t*)encoder->pval) = val;
    }
    else if(encoder->memtype == enU32){
        (*(uint32_t*)encoder->pval) = val;
    }
}

/*!****************************************************************************
* @brief
*/
uint8_t enAdd(encoder_t *encoder, int32_t val){
    int32_t temp;
    //uint8_t retval;
    
    temp = enReadVal(encoder);
    temp += val;
    
    if(encoder->mode == enCIRC){
        if(temp < encoder->min){
            enWriteVal(encoder, encoder->max);
            return enNoLim;
        }
        if(temp >= encoder->max){
            enWriteVal(encoder, encoder->min);
            return enNoLim;
        }
    }
    //(enco.mode == enNONCIRC)
    else{
        if(temp < encoder->max){
            enWriteVal(encoder, encoder->min);
            return enLimDown;
        }
        if(temp > encoder->max){
            enWriteVal(encoder, encoder->max);
            return enLimUp;
        }
    }
    enWriteVal(encoder, temp);
    return enNoLim;
}

/*!****************************************************************************
* @brief
*/
uint8_t enBigStepUp(encoder_t *encoder){
    return enAdd(encoder, encoder->bigStep);
}

/*!****************************************************************************
* @brief
*/
uint8_t enBigStepDown(encoder_t *encoder){
    return enAdd( encoder, -encoder->bigStep );
}

/*!****************************************************************************
* @brief  Прочитать значние из экодера
*/
void enGet(encoder_t *encoder)
{
    int32_t             temp;
    int64_t             temp2;

    temp = encoder->tim->CNT - (0xFFFF / 4) / 2;
    encoder->tim->CNT = (0xFFFF / 4) / 2;
    if(temp > 0){
        temp = (temp + 2) / 4;
    }else{
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
    temp = temp * encoder->step; //Шаг
    temp2 = enReadVal(encoder);
    temp2 += temp;
        
    if(encoder->mode == enCIRC){
        if(temp2 < encoder->min){
            enWriteVal(encoder, encoder->max);
            //enWriteVal(dst, enco.top + temp + 1);
            return;
        }
        if(temp2 > encoder->max){
            enWriteVal(encoder, encoder->min);
            //enWriteVal(dst, enco.bot + temp - 1);
            return;
        }
    }else{
        if(temp2 < encoder->min){
            enWriteVal(encoder, encoder->min);
            return;
        }
        if(temp2 > encoder->max){
            enWriteVal(encoder, encoder->max);
            return;
        }
    }

    if(encoder->memtype == enU8){
        *(uint8_t*)encoder->pval += temp;
    }
    else if(encoder->memtype == enU16){
        *(uint16_t*)encoder->pval += temp;
    }
    else if(encoder->memtype == enU32){
        *(uint32_t*)encoder->pval += temp;
    }
}

/******************* (C) COPYRIGHT ***************** END OF FILE ********* D_EL *****/
