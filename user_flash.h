#ifndef __INTERNAL_FLASH_H
#define __INTERNAL_FLASH_H

#define FLASH_USER_START_ADDR 0x08020000
#define FLASH_USER_END_ADDR 0x0803FFFF

#define FLASE_PAGE_SIZE 2048
#define FLASH_DATA_SIZE 256

extern uint8_t data[FLASH_DATA_SIZE];        // 数据数组
extern uint64_t data64[FLASH_DATA_SIZE / 8]; // 数组转换为64位

uint32_t Flash_Write_Data(uint32_t StartSectorAddress, uint64_t *Data);
uint32_t Flash_Read_Data(uint32_t StartSectorAddress, uint8_t *Data);
#endif