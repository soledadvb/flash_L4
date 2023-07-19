#include "main.h"
#include "user_flash.h"



uint8_t data[FLASH_DATA_SIZE];        // 数据数组
uint64_t data64[FLASH_DATA_SIZE / 8]; // 数组转换为64位

// 写入flash的函数
uint32_t Flash_Write_Data(uint32_t StartSectorAddress, uint64_t *Data)
{
    static FLASH_EraseInitTypeDef EraseIniitStruct;
    uint32_t PageError;

    HAL_FLASH_Unlock();

    EraseIniitStruct.TypeErase = FLASH_TYPEERASE_PAGES; // 设置擦除类型为页擦除
    EraseIniitStruct.Page = (StartSectorAddress - FLASH_BASE) / FLASH_PAGE_SIZE;
    EraseIniitStruct.NbPages = 1;

    if (HAL_FLASHEx_Erase(&EraseIniitStruct, &PageError) != HAL_OK) // 擦除指定页，如果失败则返回错误码
        return HAL_FLASH_GetError();
    for (int i = 0; i < FLASH_DATA_SIZE / 8; i++)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, StartSectorAddress + i * 8, Data[i]) == HAL_OK)
            StartSectorAddress += 8;
        else
            return HAL_FLASH_GetError();
    }
    HAL_FLASH_Lock();
    return HAL_OK;
}

uint32_t Flash_Read_Data(uint32_t StaartSectorAddress, uint8_t *Data)
{
    for (int i = 0; i < FLASH_DATA_SIZE; i++)
    {
        Data[i] = *(__IO uint8_t *)(StaartSectorAddress + i); // 将flash地址对应的值赋给数据数组
    }
    return HAL_OK;
}