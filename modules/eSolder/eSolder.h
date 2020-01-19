#ifndef E_SOLDER_H_
#define E_SOLDER_H_

#include "stm32f4xx.h"
#include "eSolderConstants.h"


typedef struct Device_t
{
    uint8_t enabled;
    uint8_t connected;
    uint8_t criticalError;
}Device_t;

typedef struct solder_t
{
    uint32_t tempSet;
    uint32_t tempReal;
    uint16_t coldJunctionTemp;
    Device_t devParam;
}solder_t;

typedef struct dry_t
{
    uint32_t tempSet;
    uint32_t tempReal;
    uint16_t coldJunctionTemp;
    uint8_t  flowSet;
    Device_t devParam;
}dry_t;


typedef struct eSolder_t
{
    solder_t solder;
    dry_t    dry;
    uint16_t internalTemp;
}eSolder_t;

typedef struct eSolderStoreParam_t
{
    uint16_t dummy; // TODO: need release! 
}eSolderStoreParam_t;


extern eSolder_t eSolder;

void eSolderInit(void);

#endif //!E_SOLDER_H_