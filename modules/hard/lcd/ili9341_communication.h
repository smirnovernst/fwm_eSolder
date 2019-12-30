#ifndef ILI9341_COMMUNICATION_H_
#define ILI9341_COMMUNICATION_H_

void ili9341_InitCommunication(void);
void ili9341_WriteData(uint16_t Data);
void ili9341_WriteCommand(uint8_t command);
void ili9341_WriteData_16(uint16_t data);
void ili9341_ReadData(uint8_t* response, int count);

#endif // !ILI9341_COMMUNICATION_H_
