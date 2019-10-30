#ifndef beep_h
#define beep_h
/*!****************************************************************************
* Include
*/

//Device files
#include "global_inc.h"
/*!****************************************************************************
* User define
*/
#define BEEP_TIM_CH 1

#define BEEP_TASK_PRIORITY 
 
/*!****************************************************************************
* User enum
*/

/*!****************************************************************************
* User typedef
*/
struct beep_sound_t
{
  uint16_t Frequency; 
  uint16_t Time;
};
/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
void beep_init(TIM_TypeDef *tim);
void beep(TIM_TypeDef *tim, uint16_t freq, uint16_t time);
void beep_on(TIM_TypeDef *tim, uint16_t freq);
void beep_off(TIM_TypeDef *tim);
//void beep_sound(TIM_TypeDef *tim, beep_sound_t *music, uint16_t count);

#endif //beep_h



