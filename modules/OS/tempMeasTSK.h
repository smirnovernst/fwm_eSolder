/*
*@File      tempMeasTSK.h 
*@Author    EricMarina
*@Version   
*@Date      16.06.2017
*@Breif     
*/
#ifndef tempMeasTSK_h
#define tempMeasTSK_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"


#include "stationState.h"
#include "errorHandlers.h"

#include "math.h"
/*!****************************************************************************
* User define
*/
#define TEMP_MEASURE_PERIOD   220//[ms]

#define MAX_TICKS_WAIT_RESPONSE 1000
/*!****************************************************************************
* User enum
*/

/*!****************************************************************************
* User typedef
*/

/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
__task void tempMeasTSK(void);
#endif //tempMeasTSK_h



