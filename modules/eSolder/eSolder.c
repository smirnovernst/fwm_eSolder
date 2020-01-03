#include "eSolder.h"

eSolder_t eSolder = {
    .solder = {
        .tempSet = ESOLDER_TEMP_SET_DEFAULT,
    },
    .dry = {
        .tempSet = ESOLDER_TEMP_SET_DEFAULT,
        .flowSet = ESOLDER_FLOW_SET_DEFAULT
    }
};

void eSolderInit(void)
{

}