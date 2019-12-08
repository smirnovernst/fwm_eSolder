/*
*@File          regulator.c
*@Author        User
*@Version       
*@Date          06.09.2018
*@Breif         
*/
/*!****************************************************************************
* Include
*/
#include "regulator.h"
/*!****************************************************************************
* Memory
*/
regulator_t regulatorPll;
regulator_t regulatorSolder;
/*!****************************************************************************
* irq
*/

__irq void TIM1_CC_IRQHandler(void)
{
    
    GPIO_PIN_SET(GPIOC, 0);
   
    regulatorCompute(&regulatorPll);
    regulatorCompute(&regulatorSolder);
    
    GPIO_PIN_RESET(GPIOC, 0);
    
    TIM1->SR = ~TIM_SR_CC1IF;                   //Clear flag 
}
/*!****************************************************************************
* Functions
*/


inline void regulatorCompute(regulator_t *regulator)
{
    if (regulator->state == regulatorState_WAITOFF)
    {
        regulator->hardCntrlReg &=  ~regulator->enableMask;
        regulator->state = regulatorState_OFF;
        return;
    }
    
    regulator->pid.term.Fbk = *(regulator->pFbk);
    if (regulator->pid.term.Ref != 0){
        regulator->pid.term.Ref = *(regulator->pRef);
    }
   
    PID_GRANDO_IQ_FUNC(&regulator->pid);
    *regulator->pOut = 65535 - regulator->pid.term.Out;
}


void regulatorHard_init()
{
     //TIM Configuration
    RCC->APB2ENR    |= RCC_APB2ENR_TIM1EN;      //TIM1 Enable clock
    RCC->APB2RSTR   |= RCC_APB2RSTR_TIM1RST;    //TIM1 Reset
    RCC->APB2RSTR   &= ~RCC_APB2RSTR_TIM1RST;
    
    //gpioInit(GPIOA, 8, gpioMode_IN, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, 0); //ZC
    //gpioInit(GPIOA, 9, gpioMode_IN, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, 0); //dry
    //gpioInit(GPIOA, 10, gpioMode_IN, gpioPuPd_PULLDOWN, gpioType_PUSHPULL, 0);//solder
    
    TIM1->PSC       = 16;                        //1 tic = 250ns for freq = 24 Mhz
    TIM1->ARR       = APB2_FREQUENCY / TIM1->PSC / 55;
    
    //Capture (CH1)
    TIM1->CCMR1     |= TIM_CCMR1_IC1F_2 |       //Input capture 1 filter - SAMPLING=fDTS/4, N=8
                       TIM_CCMR1_IC1F_1 |
                       TIM_CCMR1_IC1F_0 |
                       TIM_CCMR1_IC1F_3;
    
    TIM1->CCMR1     |= TIM_CCMR1_CC1S_0;        //CC1 channel is configured as input, IC1 is mapped on TI1
    TIM1->CCER      |= TIM_CCER_CC1P;           //Capture is done on a falling edge of IC1. When used as external trigger, IC2 is inverted
    TIM1->CCER      |= TIM_CCER_CC1E;           //Capture/Compare 1 output enable
    TIM1->DIER      |= TIM_DIER_CC1IE;	        //Capture/Compare 1 interrupt enable
    
    //Compare (CH2)
    TIM1->CCER      |= TIM_CCER_CC2E;           //Capture/Compare 2 output enable
    TIM1->CCER      |= TIM_CCER_CC2P;           //inverting polarity
    TIM1->CCMR1     |= TIM_CCMR1_OC2M;          //PWM mode 2 (INVERT PWM)                                        
    TIM1->BDTR      |= TIM_BDTR_MOE;
    TIM1->CCR2      = 1000;                     
    
    //Compare (CH3)
    TIM1->CCER      |= TIM_CCER_CC3E;           //Capture/Compare 3 output enable
    TIM1->CCER      |= TIM_CCER_CC3P;           //inverting polarity
    TIM1->CCMR2     |= TIM_CCMR2_OC3M;          //PWM mode 3 (INVERT PWM)                                        
    TIM1->BDTR      |= TIM_BDTR_MOE;
    TIM1->CCR3      = 0;   
     
}
void regulatorPhase_init()
{
      //PID PLL Init
    PID_GRANDO_IQ_init(&regulatorPll.pid);
    regulatorPll.pid.param.Kr   = _IQ(1.0);               //Parameter: reference set-point weighting
    regulatorPll.pid.param.Kp   = _IQ(1);                 //Parameter: proportional loop gain
    regulatorPll.pid.param.Ki   = _IQ(0.0);               //Parameter: integral gain
    regulatorPll.pid.param.Kd   = _IQ(0.000);             //Parameter: derivative gain
    regulatorPll.pid.param.Km   = _IQ(1.0);               //Parameter: derivative weighting
    regulatorPll.pid.param.Umax = 65000;
    regulatorPll.pid.param.Umin = 0;
    regulatorPll.pid.term.Ref = 25000; 
    
    regulatorPll.pFbk = TIM1->CCR1;
    regulatorPll.pOut = TIM1->ARR; 
    regulatorPll.pRef = 0;
    
    
}
void regulatorSolder_init()
{
    //PID Init
   PID_GRANDO_IQ_init(&regulatorSolder.pid);
   regulatorSolder.pid.param.Kr   = _IQ(1.0);                 //Parameter: reference set-point weighting
   regulatorSolder.pid.param.Kp   = _IQ(500);                   //Parameter: proportional loop gain
   regulatorSolder.pid.param.Ki   = _IQ(1.0);                 //Parameter: integral gain
   regulatorSolder.pid.param.Kd   = _IQ(1.000);               //Parameter: derivative gain
   regulatorSolder.pid.param.Km   = _IQ(1.0);                 //Parameter: derivative weighting
   regulatorSolder.pid.param.Umax = 65535;
   regulatorSolder.pid.param.Umin = 0;
   regulatorSolder.pid.term.Ref = 0;
   
   regulatorSolder.pOut = &TIM1->CCR3;
   regulatorSolder.pFbk = &stationState.solder.temperatueReal;
   regulatorSolder.pRef = &stationState.solder.temperatueSet;
   
}

void regulatorInit()
{
    regulatorPhase_init();
    regulatorSolder_init();
    regulatorHard_init();
    //need add enable regulator
}


