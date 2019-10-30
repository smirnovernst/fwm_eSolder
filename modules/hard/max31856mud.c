/*
*@File          max31856mud.c
*@Author        Ernst
*@Version       
*@Date          21.08.2018
*@Breif         
*/
/*!****************************************************************************
* Include
*/
#include "max31856mud.h"
#include "GPIO.h"
#include <string.h>
/*!****************************************************************************
* Define
*/
#define MAX31856_ADDR_CR0       (0x00) //Configuration 0 Register
#define MAX31856_ADDR_CR1       (0x01) //Configuration 1 Register
#define MAX31856_ADDR_MASK      (0x02) //Fault Mask Register
#define MAX31856_ADDR_CJHF      (0x03) //Cold-Junction High Fault Threshold
#define MAX31856_ADDR_CJLF      (0x04) //Cold-Junction Low Fault Threshold
#define MAX31856_ADDR_LTHFTH    (0x05) //Linearized Temperature High Fault Threshold MSB
#define MAX31856_ADDR_LTHFTL    (0x06) //Linearized Temperature High Fault Threshold LSB
#define MAX31856_ADDR_LTLFTH    (0x07) //Linearized Temperature Low Fault Threshold MSB
#define MAX31856_ADDR_LTLFTL    (0x08) //Linearized Temperature Low Fault Threshold LSB
#define MAX31856_ADDR_CJTO      (0x09) //Cold-Junction Temperature Offset Register
#define MAX31856_ADDR_CJTH      (0x0A) //Cold-Junction Temperature Register, MSB
#define MAX31856_ADDR_CJTL      (0x0B) //Cold-Junction Temperature Register, LSB
#define MAX31856_ADDR_LTCBH     (0x0c) //Linearized TC Temperature, Byte 2
#define MAX31856_ADDR_LTCBM     (0x0D) //Linearized TC Temperature, Byte 1
#define MAX31856_ADDR_LTCBL     (0x0E) //Linearized TC Temperature, Byte 0
#define MAX31856_ADDR_SR        (0x0F) //Fault Status Register
/*!****************************************************************************
* Memory
*/
/*!****************************************************************************
* Memory
*/
/*!****************************************************************************
* Functions
*/
void max31856mud_init(max31856mud_t *max31856mud)
{
    spi_disable(max31856mud->spi);  //for reboot max31856mud need set Hi-z on the spi pins
    vTaskDelay((TickType_t)100/portTICK_PERIOD_MS);
    spi_enable(max31856mud->spi);   // 
    
    max31856mud->state = max31856State_NOINIT;
   //**********Check default param****************//
    const uint8_t default_value[16] = {0x00, 0x03, 0xFF, 0x7F, 0xC0, 0x7F, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t read_value[16];
    max31856mud_read(max31856mud, MAX31856_ADDR_CR0, read_value, sizeof(default_value));
    
    if (memcmp(read_value, default_value, sizeof(default_value)) == 0)
    {
        max31856mud->state = max31856State_OK;
    }
    else
    {
        max31856mud->state = max31856State_ERRINIT;
    }
}

void max31856mud_read(max31856mud_t *max31856mud, uint8_t addr, uint8_t *buffer, uint8_t size)
{
    uint8_t readNull, ret = 0;
    GPIO_PIN_RESET(max31856mud->portCS, max31856mud->pinCS);
    ret += spi_tranceive(&spi1, &addr, size+1, MAX31856MUD_TIMEOUT);
    ret += spi_receive(&spi1, &readNull, 1, MAX31856MUD_TIMEOUT); //first byte receive - not valid
    ret += spi_receive(&spi1, buffer, size, MAX31856MUD_TIMEOUT);
    GPIO_PIN_SET(max31856mud->portCS, max31856mud->pinCS);
    if (ret != 0) {max31856mud->state = max31856State_ERRCOMM;}
    //else { max31856mud->state = max31856State_OK; }     
}

void max31856mud_write(max31856mud_t *max31856mud, uint8_t addr, uint8_t data)
{
    addr |=0x80;
    uint8_t buffer[2];
    buffer[0] = addr;
    buffer[1] = data; 
    
    GPIO_PIN_RESET(max31856mud->portCS, max31856mud->pinCS);
    uint8_t ret = spi_tranceive(&spi1, buffer, 2, MAX31856MUD_TIMEOUT);
    GPIO_PIN_SET(max31856mud->portCS, max31856mud->pinCS);
    if (ret != 0) {max31856mud->state = max31856State_ERRCOMM;}
    //else { max31856mud->state = max31856State_OK; }
}
void max31856mud_oneShot(max31856mud_t *max31856mud)
{
    uint8_t CR0 = 0;
    max31856mud_read(max31856mud, MAX31856_ADDR_CR0, &CR0, 1);
    CR0 |= 0x40; //1SHOT bit
    max31856mud_write(max31856mud, MAX31856_ADDR_CR0, CR0);
}
void max31856mud_startConvMode(max31856mud_t *max31856mud)
{
    uint8_t CR0 = 0;
    max31856mud_read(max31856mud, MAX31856_ADDR_CR0, &CR0, 1);
    CR0 |= 0x80; //CMODE bit
    max31856mud_write(max31856mud, MAX31856_ADDR_CR0, CR0);
}
void max31856mud_stopConvMode(max31856mud_t *max31856mud)
{
    uint8_t CR0 = 0;
    max31856mud_read(max31856mud, MAX31856_ADDR_CR0, &CR0, 1);
    CR0 &= ~0x80; //CMODE bit
    max31856mud_write(max31856mud, MAX31856_ADDR_CR0, CR0);
}
int16_t max31856mud_getColdJunctionTemp(max31856mud_t *max31856mud)
{ 
    uint8_t buffer[2];
    max31856mud_read(max31856mud, MAX31856_ADDR_CJTH, buffer, 2);
    int16_t ColdJunctionTemp = 0;
    ColdJunctionTemp |=  (*buffer << 8) | *(buffer+1);
    return ColdJunctionTemp;
}
int32_t max31856mud_getLinearizedTemp(max31856mud_t *max31856mud)
{
    uint8_t buffer[3];
    max31856mud_read(max31856mud, MAX31856_ADDR_LTCBH, buffer, 3);
    int32_t LinearizedTemp = 0;
    LinearizedTemp = (*buffer << 24) | (*(buffer+1) << 16) | *(buffer + 3) << 8;
    return LinearizedTemp;
}