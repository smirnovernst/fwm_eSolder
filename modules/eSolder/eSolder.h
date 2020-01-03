#ifndef E_SOLDER_H_
#define E_SOLDER_H_

#include "stm32f4xx.h"
#include "eSolderConstants.h"

typedef struct solder_t
{
    uint16_t tempSet;
    uint16_t tempReal;
    uint8_t  enabled;
    uint8_t  connected;
}solder_t;

typedef struct dry_t
{
    uint16_t tempSet;
    uint16_t tempReal;
    uint8_t  flowSet;
    uint8_t  enabled;
    uint8_t  connected;
}dry_t;


typedef struct eSolder_t
{
    solder_t solder;
    dry_t   dry;
}eSolder_t;

typedef struct eSolderStoreParam_t
{
    uint16_t dummy; // TODO: need release! 
}eSolderStoreParam_t;


extern eSolder_t eSolder;

void eSolderInit(void);

#endif //!E_SOLDER_H_