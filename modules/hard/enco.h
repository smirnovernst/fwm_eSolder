/*!****************************************************************************
* @file    enco.h
* @author  Storozhenko Roman - D_EL
* @version V2.3
* @date    13-05-2015 
* @brief   Средства работы с энкодером
*/
#ifndef ENCO_H
#define ENCO_H

#include "global_inc.h"
#include "GPIO.h"
/*!****************************************************************************
* User define
*/

/*!****************************************************************************
* User typedef
*/
typedef enum{
    enNONCIRC,
    enCIRC
}enMode_type;

typedef enum{
    enU8,
    enU16,
    enU32
}enMemType_type;

typedef enum{
    enNoLim,
    enLimUp,
    enLimDown
}enLimType_type;

typedef struct{
    void            *pval;
    uint16_t        min;
    uint16_t        max;
    uint16_t        step;
    uint16_t        bigStep;
    enMode_type     mode;
    enMemType_type  memtype;
    TIM_TypeDef*    tim;
}encoder_t;

typedef struct
{
    TIM_TypeDef*    tim;
    GPIO_TypeDef*   gpioA;
    GPIO_TypeDef*   gpioB;
    uint8_t         pinA;
    uint8_t         pinB;
    
    
}encoderInit_t;

/*!****************************************************************************
* Extern viriables
*/

extern encoder_t encSolder, encDry;
/*!****************************************************************************
* Macro functions
*/
#define enEnable(_encoder)      _encoder.tim->CR1   |= TIM_CR1_CEN;
#define enDisable(_encoder)     _encoder.tim->CR1   &= ~TIM_CR1_CEN;

#define enGeReg()       (EnReg >> NSHIFT)
#define enSet(_encoder, _enMin, _enMax, _step, _bigStep, _enmode, _memtype, _pval)     \
    _encoder.min        = _enMin;                               \
    _encoder.max        = _enMax;                               \
    _encoder.step       = _step;                                \
    _encoder.bigStep    = _bigStep;                             \
    _encoder.mode       = _enmode;                              \
    _encoder.memtype    = _memtype;                             \
    _encoder.pval       = _pval;

/*!****************************************************************************
* Prototypes for the functions
*/
void encoderInit(encoder_t *encoder, encoderInit_t *encoderInit);
uint32_t enReadVal(encoder_t *encoder);
void enWriteVal(encoder_t *encoder, int32_t val);
uint8_t enAdd(encoder_t *encoder, int32_t val);
uint8_t enBigStepUp(encoder_t *encoder);
uint8_t enBigStepDown(encoder_t *encoder);
void enGet(encoder_t *encoder);

#endif //ENCO_H
/*************** (C) COPYRIGHT ************** END OF FILE ********* D_EL *****/
