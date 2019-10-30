/*
*@File      tempMeasTSK.c 
*@Author    EricMarina
*@Version   
*@Date      16.06.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "tempMeasTSK.h"


/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Prototypes
*/
static inline float movingAverageFilter(float *src, uint8_t with);

/*!****************************************************************************
* Functions
*/
#if 0
//<<TODO: need release for stm32f4
void TIM6_IRQHandler(void)
{ 
    TIM6->SR = 0;
    BaseType_t  xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    
    xSemaphoreGiveFromISR(tempMeasSemStart, &xHigherPriorityTaskWoken);
    if(xHigherPriorityTaskWoken != pdFALSE)
    {
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
}


__task void tempMeasTSK(void)
{
    
    /*=========== Initialisation ==========*/
    spi_t max6675_solder, max6675_dry;
     
    
    max6675_solder.spi = SPI2;
    max6675_solder.cs.port = GPIOB;
    max6675_solder.cs.pin = 12;
    max6675_solder.dev = SPI_DEV_MASTER;
    max6675_solder.mode = SPI_MODE_0;
    max6675_solder.clock = SPI_CLOCK_FPCLK_DIV_32;
   
    max6675_dry.spi = SPI3;
    max6675_dry.cs.port = GPIOA;
    max6675_dry.cs.pin = 4;
    max6675_dry.dev = SPI_DEV_MASTER;
    max6675_dry.mode = SPI_MODE_0;
    max6675_dry.clock = SPI_CLOCK_FPCLK_DIV_32;
    
    max6675_init(&max6675_solder);
    max6675_init(&max6675_dry);
    
    /*=========== TIM6 init ==========*/
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    
    TIM6->DIER |= TIM_DIER_UIE;
    TIM6->PSC = 7200;
    TIM6->ARR = TEMP_MEASURE_PERIOD*10;
    TIM6->CR1 |= TIM_CR1_CEN;
    
    NVIC_SetPriority(TIM6_IRQn, 3);  
    NVIC_EnableIRQ(TIM6_IRQn);
    /*=========== Memory ==========*/
    uint16_t solderReceive, dryReceive;
    max6675Data_t solderData, dryData;
    float solderTemp[8], dryTemp[8];
    
    uint8_t i=0;
    
    /*=========== task ==========*/
    while(1)
    {       
   

        
        
       xSemaphoreTake(tempMeasSemStart, portMAX_DELAY);

        max6675_readData(&max6675_solder, &solderReceive);
        max6675_readData(&max6675_dry, &dryReceive);
        
        
        if(xSemaphoreTake(max6675_solderSem, ( TickType_t )MAX_TICKS_WAIT_RESPONSE ) != pdTRUE )
        {
            tempMeasErr();
        }
        
        if(xSemaphoreTake(max6675_drySem, ( TickType_t )MAX_TICKS_WAIT_RESPONSE) != pdTRUE )
        {
            tempMeasErr();
        }
        
        max6675_decodeData(&solderReceive, &solderData);
        max6675_decodeData(&dryReceive, &dryData);
        
        if (solderData.OC_fault)
        {
            connectionErr(&stationState.solder);
        }
        else
        {
            stationState.solder.connection = 1;
        }
        if (dryData.OC_fault)
        {
             connectionErr(&stationState.dry);
        }
        else
        {
             stationState.dry.connection = 1;
        }
        
        stationState.solder.temperatueReal = (int16_t)floorf( solderData.temperature);
        stationState.dry.temperatueReal = (int16_t)floorf( dryData.temperature);
   
//          solderTemp[i] = (int16_t)solderData.temperature;
//           dryTemp[i] = (int16_t)dryData.temperature;
//           i++;
//       if(i > 7) 
//        {
//            i = 0;
//           
//           
//             stationState.solder.temperatueReal =  (uint16_t)floorf( movingAverageFilter(solderTemp, 8) );
//             stationState.dry.temperatueReal = (uint16_t)floorf( movingAverageFilter(dryTemp, 8) );
//            
//            xSemaphoreGive(tempMeasSemEnd);
//            
//        }
        
        vTaskDelay(10/ portTICK_PERIOD_MS);
        
    }
}

static inline float movingAverageFilter(float *src, uint8_t with)
{
    float     *dataEnd = src + with;
    float     sum = 0;
    
    if(with == 1){
        return *src;
    }

    
    while(src < dataEnd){   //Накопление
        sum += *src++;
        sum += *src++;
        sum += *src++;
        sum += *src++;
        sum += *src++;
        sum += *src++;
        sum += *src++;
        sum += *src++;
    }
    return ((sum + (with>>1)) / with);
}
#endif //if 0

__task void tempMeasTSK(void)
{
    //<<TODO: for build
}