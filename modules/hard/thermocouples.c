#include "max31856mud.h"
#include "Drivers/spi/spi1.h"

max31856mud_t thermocoupleSolder = {
    .pSpi = &spi1,
    .portCS = GPIOA,
    .pinCS = 4
};
max31856mud_t thermocoupleDry = {
    0
};