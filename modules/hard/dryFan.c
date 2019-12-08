/*
*@File      dryFan.c 
*@Author    EricMarina
*@Version   
*@Date      05.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "dryFan.h"
#include "math.h"
/*!****************************************************************************
* Memory
*/
static pwmChannel_t pwm_dryFan;
/*!****************************************************************************
* Functions
*/
void dryFan_init()
{
    pwm_dryFan.tim = TIM5;
    pwm_dryFan.channel = 3;
    
    pwm_channelInit(&pwm_dryFan, GPIOA, 2);
}
void dryFan_setFlow(uint8_t flow)
{
    float flow_calc;
    if (flow < 100)
    {
        flow_calc = flow*0.10+0.0014*flow*flow;
    }
    else flow_calc = 100;
    
    pwm_dutySet(&pwm_dryFan, flow_calc); 
}


