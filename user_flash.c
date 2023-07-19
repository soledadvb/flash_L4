#include "main.h"
#include "user_flash.h"



uint8_t data[FLASH_DATA_SIZE];        // ��������
uint64_t data64[FLASH_DATA_SIZE / 8]; // ����ת��Ϊ64λ

// д��flash�ĺ���
uint32_t Flash_Write_Data(uint32_t StartSectorAddress, uint64_t *Data)
{
    static FLASH_EraseInitTypeDef EraseIniitStruct;
    uint32_t PageError;

    HAL_FLASH_Unlock();

    EraseIniitStruct.TypeErase = FLASH_TYPEERASE_PAGES; // ���ò�������Ϊҳ����
    EraseIniitStruct.Page = (StartSectorAddress - FLASH_BASE) / FLASH_PAGE_SIZE;
    EraseIniitStruct.NbPages = 1;

    if (HAL_FLASHEx_Erase(&EraseIniitStruct, &PageError) != HAL_OK) // ����ָ��ҳ�����ʧ���򷵻ش�����
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
        Data[i] = *(__IO uint8_t *)(StaartSectorAddress + i); // ��flash��ַ��Ӧ��ֵ������������
    }
    return HAL_OK;
}