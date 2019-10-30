/*
*@File          max31856mud.h
*@Author        Ernst
*@Version       
*@Date          21.08.2018
*@Breif         
*/
#ifndef  max31856mud_h
#define  max31856mud_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"

#include "spi_f4.h"
/*!****************************************************************************
* User define
*/
#define MAX31856MUD_TIMEOUT     (1000)//[mS]
/*!****************************************************************************
* User enum
*/
typedef enum
{
    max31856State_NOINIT,
    max31856State_INITED,
    max31856State_OK,
    max31856State_FAIL,
    max31856State_ERRCOMM,
    max31856State_ERRINIT
}max31856State_t;
typedef enum
{
    max31856CoupleType_B = 0x0,
    max31856CoupleType_E,
    max31856CoupleType_J,
    max31856CoupleType_K,
    max31856CoupleType_N,
    max31856CoupleType_R,
    max31856CoupleType_S,
    max31856CoupleType_T,
    max31856CoupleType_VOLTMODE_8 = 0x8,    // Voltage Mode, Gain = 8. Code = 8 x 1.6 x 217 x VIN
    max31856CoupleType_VOLTMODE_32 = 0xC,   // Voltage Mode, Gain = 32. Code = 32 x 1.6 x 217 x VIN
}max31856CoupleType_t;

/*!****************************************************************************
* User typedef
*/
typedef struct
{
    spi_t               *spi;
    GPIO_TypeDef        *portCS;
    uint8_t             pinCS;
    max31856State_t     state;
}max31856mud_t;
/*!****************************************************************************
* Extern viriables
*/
/*!****************************************************************************
* Macro functions
*/
/*!****************************************************************************
* Prototypes for the functions
*/
void max31856mud_init(max31856mud_t *max31856mud);
void max31856mud_read(max31856mud_t *max31856mud, uint8_t addr, uint8_t *buffer, uint8_t size);
void max31856mud_write(max31856mud_t *max31856mud, uint8_t addr, uint8_t data);
void max31856mud_oneShot(max31856mud_t *max31856mud);
void max31856mud_startConvMode(max31856mud_t *max31856mud);
void max31856mud_stopConvMode(max31856mud_t *max31856mud);
int16_t max31856mud_getColdJunctionTemp(max31856mud_t *max31856mud);
int32_t max31856mud_getLinearizedTemp(max31856mud_t *max31856mud);
#endif  //max31856mud_h
