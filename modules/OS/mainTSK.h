/*
*@File      mainTSK.h
*@Author    smirnovernst
*@Version
*@Date      04.11.2019
*@Breif
*/
#ifndef MAINTSK_H_
#define MAINTSK_H_
/*!****************************************************************************
* Include
*/

/*!****************************************************************************
* User define
*/
/*!****************************************************************************
* User enum
*/
typedef enum {
    
    mainTskEncoderSelected_SOLDER_TEMP = 0,
    mainTskEncoderSelected_DRY_TEMP,
    mainTskEncoderSelected_DRY_FLOW,
    mainTskEncoderSelected_END,
}mainTskEncoderSelected_t;
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
mainTskEncoderSelected_t mainTsk_GetEncoderSelected(void);

__task void mainTsk(void);
#endif //MAINTSK_H_


