/*
*@File          pwmController.h
*@Author        User
*@Version       
*@Date          09.09.2018
*@Breif         
*/
#ifndef  pwmController_h
#define  pwmController_h
/*!****************************************************************************
* Include
*/
/*!****************************************************************************
* User define
*/
/*!****************************************************************************
* User enum
*/
/*!****************************************************************************
* User typedef
*/
typedef struct
{
    uint8_t     enable :1;
    uint32_t    *pCounterReg;
    
}pwmChannel_t;
typedef struct
{
    uint32_t        *pTimer;
    pwmChannel_t    Ch1;
    uint8_t         enable :1;
}pwmController_t;
/*!****************************************************************************
* Extern viriables
*/
/*!****************************************************************************
* Macro functions
*/
/*!****************************************************************************
* Prototypes for the functions
*/
#endif  //pwmController_h
