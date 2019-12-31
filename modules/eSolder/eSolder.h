#ifndef E_SOLDER_H_
#define E_SOLDER_H_

#include "stm32f4xx.h"
#include "eSolderConstants.h"

typedef struct eSolder_t
{
    uint16_t solderTempSet;
    uint16_t solderTempReal;
    uint8_t  solderEnabled;

    uint16_t dryTempSet;
    uint16_t dryTempReal;
    uint8_t dryFlowSet;
    uint8_t dryEnabled;
}eSolder_t;

typedef struct eSolderStoreParam_t
{
    uint16_t dummy; // TODO: need release! 
}eSolderStoreParam_t;


extern eSolder_t eSolder;

void eSolderInit(void);

#endif //!E_SOLDER_H_