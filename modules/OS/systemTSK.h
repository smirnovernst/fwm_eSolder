/*
*@File      systemTSK.h 
*@Author    EricMarina
*@Version   
*@Date      01.07.2017
*@Breif     
*/
#ifndef systemTSK_h
#define systemTSK_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"

#include "stationState.h"
#include "UI.h"
#include "keyboard.h"
#include "enco.h"
#include "dryFan.h"


#include "regulator.h"
/*!****************************************************************************
* User define
*/
#define DBG_FAILOUTOFF_DISABLE  (1)
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
__task void systemTSK(void);

#endif //systemTSK_h



