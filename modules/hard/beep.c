/*!****************************************************************************
* Include
*/
#include "beep.h"

/*!****************************************************************************
* Functions
*/

void beep_init(TIM_TypeDef *tim)
{
   tim->CR1 = 0;
   
#if BEEP_TIM_CH == 1 
   tim->CCMR1 &= ~TIM_CCMR1_OC1M;
   tim->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
   
   tim->CCER  = TIM_CCER_CC1E;
#endif
   
#if BEEP_TIM_CH == 2 
   tim->CCMR1 &= ~TIM_CCMR1_OC2M;
   tim->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;   
   
   tim->CCER  = TIM_CCER_CC2E;
#endif

#if BEEP_TIM_CH == 3 
   tim->CCMR2 &= ~TIM_CCMR2_OC3M;
   tim->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;   
   
   tim->CCER  = TIM_CCER_CC3E;
#endif
   
#if BEEP_TIM_CH == 4 
   tim->CCMR2 &= ~TIM_CCMR2_OC4M;
   tim->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;   
   
   tim->CCER  = TIM_CCER_CC4E;
   
#endif

   tim->PSC = 9; 
 
}
 
void beep_on(TIM_TypeDef *tim, uint16_t freq)
{
  //tim->ARR = APB2_FREQUENCY / ((tim->PSC + 1) * freq);
  
#if BEEP_TIM_CH == 1 
  tim->CCR1 = tim->ARR/2;
#endif
   
#if BEEP_TIM_CH == 2 
  tim->CCR2 = tim->ARR/2;
#endif

#if BEEP_TIM_CH == 3 
  tim->CCR3 = tim->ARR/2;
#endif
   
#if BEEP_TIM_CH == 4 
  tim->CCR4 = tim->ARR/2;
#endif

  tim->CR1 |= TIM_CR1_CEN;
}

void beep_off(TIM_TypeDef *tim)
{
  tim->CR1 &= ~TIM_CR1_CEN;
}

