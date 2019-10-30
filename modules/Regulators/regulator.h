/*
*@File          regulator.h
*@Author        User
*@Version       
*@Date          06.09.2018
*@Breif         
*/
#ifndef  regulator_h
#define  regulator_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"
#include "stationState.h"
/*!****************************************************************************
* User define
*/
/*!****************************************************************************
* User enum
*/
/*!****************************************************************************
* User typedef
*/
typedef enum
{
    regulatorState_OFF = 0,
    regulatorState_RUN,
    regulatorState_WAITOFF,
    regulatorState_ERROR,
}regulatorState_t;
typedef struct
{
    PID_GRANDO_IQ_CONTROLLER pid;
    uint32_t    *pOut;
    uint32_t    *pRef;
    uint32_t    *pFbk;  
    uint32_t    *hardCntrlReg;
    uint32_t    enableMask;
    regulatorState_t state;
}regulator_t;

/*!****************************************************************************
* Extern viriables
*/
/*!****************************************************************************
* Macro functions
*/
#define regulatorOn(regulator)   regulator->hardCntrlReg |=  regulator->enableMask; regulator->state = regulatorState_RUN;
#define regulatorOff(regulator)  regulator->state = regulatorState_WAITOFF; 
/*!****************************************************************************
* Prototypes for the functions
*/
inline void regulatorCompute(regulator_t *regulator);
#endif  //regulator_h
