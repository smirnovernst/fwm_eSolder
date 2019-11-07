/*!****************************************************************************
* @file    enco.h
* @author  Storozhenko Roman - D_EL
           Smirnov Ernst 
* @version V2.3
* @date    13-05-2015, 05-11-2019
* @brief   Средства работы с энкодером
*/
#ifndef ENCODERS_H_
#define ENCODERS_H_

#include "Drivers/gpio.h"
/*!****************************************************************************
* User define
*/

/*!****************************************************************************
* User typedef
*/
typedef enum{
    enNONCIRC = 0,
    enCIRC
}enMode_type;

typedef enum{
    enU8 = 0,
    enU16,
    enU32
}enMemType_type;

typedef enum{
    enNoChanged = 0,
    enNoLim,
    enLimUp,
    enLimDown, 
    enLimNone,
}enLimType_type;

typedef struct {
    void            *pVal;
    uint16_t        min;
    uint16_t        max;
    uint16_t        step;
    uint16_t        bigStep;
    enMode_type     mode;
    enMemType_type  memtype;
}EncoderControlled;

typedef struct{
    TIM_TypeDef*        tim;
    GPIO_TypeDef*       gpioA;
    GPIO_TypeDef*       gpioB;
    uint8_t             pinA;
    uint8_t             pinB;
    uint8_t             pinA_AFnum;
    uint8_t             pinB_AFnum;
    EncoderControlled   *nowControlled;
}Encoder;


/*!****************************************************************************
* Macro functions
*/
#define encoderEnable(_encoder)      _encoder.tim->CR1   |= TIM_CR1_CEN;
#define encoderDisable(_encoder)     _encoder.tim->CR1   &= ~TIM_CR1_CEN;

#define enSet(_encoder, _enMin, _enMax, _step, _bigStep, _enmode, _memtype, _pval)  {   \
    _encoder.min        = _enMin;                               \
    _encoder.max        = _enMax;                               \
    _encoder.step       = _step;                                \
    _encoder.bigStep    = _bigStep;                             \
    _encoder.mode       = _enmode;                              \
    _encoder.memtype    = _memtype;                             \
    _encoder.pval       = _pval;                                \
    }

/*!****************************************************************************
* Prototypes for the functions
*/
void encoderInit(Encoder *encoder);
enLimType_type encoderUpdate(Encoder *encoder, EncoderControlled *controlled);

#endif //!ENCODERS_H_
/*************** (C) COPYRIGHT ************** END OF FILE ********* D_EL *****/
