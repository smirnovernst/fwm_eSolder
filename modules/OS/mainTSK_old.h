/*
*@File      mainTSK.h 
*@Author    EricMarina
*@Version   
*@Date      22.05.2017
*@Breif     
*/
#ifndef mainTSK_h
#define mainTSK_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"

#include "stationState.h"
#include "UI.h"
#include "keyboard.h"
#include "enco.h"


//FreeRTOS files 
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "OSInit.h"

/*!****************************************************************************
* User define
*/
#define TEMP_STEP       5
#define TEMP_BIGSTEP    50
#define FLOW_STEP       5
#define FLOW_BIGSTEP    10
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
__task void mainTSK(void);
#endif //mainTSK_h



