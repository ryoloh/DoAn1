#ifndef   __FLASH_H
#define 	__FLASH_H	
#include "stdint.h"
#include "string.h"


void Flash_Earse(uint32_t address);
void Flash_Write_Int(uint32_t address, int value);
void Flash_Write_Float(uint32_t address, float value);
void Flash_Write_Array(uint32_t address, uint8_t *array, uint16_t length);
uint32_t Caculate_Adress_Flash(uint32_t baseAddress, uint32_t offset);


int Flash_Read_Int(uint32_t address);
float Flash_Read_Float(uint32_t address);
void Flash_Read_Array(uint32_t address, uint8_t *array, uint16_t length);

#endif