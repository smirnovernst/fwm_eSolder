/*
*@File          regulatorSolder.h
*@Author        User
*@Version       
*@Date          06.09.2018
*@Breif         
*/
#ifndef  regulatorSolder_h
#define  regulatorSolder_h
/*!****************************************************************************
* Include
*/
#include "regulator.h"
/*!****************************************************************************
* User define
*/
/*!****************************************************************************
* User enum
*/
typedef enum {
    solderState_OFF = 0,
    solderState_RUN,
    solderState_TEMP_MEASURE_REQUEST,
    solderState_TEMP_MEASURE,
    solderState_NONE
}solderState_t
/*!****************************************************************************
* User typedef
*/
typedef (void)(*solderTempMeasureReadyCb)(void);
/*!****************************************************************************
* Extern viriables
*/
extern regulator_t regulatorSolder;
/*!****************************************************************************
* Macro functions
*/
/*!****************************************************************************
* Prototypes for the functions
*/

void solderTempMeasureRequest(void);
void solferTempMeasureSetReadyCb(solderTempMeasureReadyCb cb);
void solderRun(void);
void solderOff(void);

#endif  //regulatorSolder_h
