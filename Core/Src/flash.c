#include "flash.h"
#include "stm32f1xx.h"                  // Device header


void Flash_Earse(uint32_t address){
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef ptearse;
	ptearse.Banks = 1;
	ptearse.NbPages = 1;
	ptearse.PageAddress = address;
	ptearse.TypeErase = FLASH_TYPEERASE_PAGES;
	uint32_t pagrerr;
	HAL_FLASHEx_Erase(&ptearse,&pagrerr);
	HAL_FLASH_Lock();
}
void Flash_Write_Int(uint32_t address, int value){
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,address,value);
	HAL_FLASH_Lock();
}
void Flash_Write_Float(uint32_t address, float value){

}
void Flash_Write_Array(uint32_t address, uint8_t *array, uint16_t length){
	HAL_FLASH_Unlock();
	uint16_t *pt = (uint16_t*)array;
	for(uint16_t index = 0; index < (length +1)/2;index++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,address + 2*index, *pt);
		pt++;
	}
	
	HAL_FLASH_Lock();
}


int Flash_Read_Int(uint32_t address){
 return *(__IO uint16_t *)(address);
}

void Flash_Read_Array(uint32_t address, uint8_t *array, uint16_t length){
	uint8_t *pt = (uint8_t*)array;
	for(uint8_t index = 0; index < length;index++){
		*pt = *(__IO uint8_t *)(address +index);
		pt++;
	}
}
uint32_t Caculate_Adress_Flash(uint32_t baseAddress, uint32_t offset){
	uint32_t result = baseAddress + offset*1024;
	return result;
}




