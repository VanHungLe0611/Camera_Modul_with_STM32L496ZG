/*
 * fmc_driver.c
 *
 *  Created on: 22.08.2019
 *      Author: hungv
 */

#include "fmc_driver.h"
#include "var_interface.h"

uint8_t aRxBuffer[IMAGE_SIZE] = { 0 };

void FMC_Init_Default(void) {
	/*Read NOR memory ID*/
	HAL_NOR_Read_ID(&hnor1, &NOR_Id);

//	/* Test the NOR ID correctness */
//	if ((NOR_Id.Manufacturer_Code != (uint16_t) MANUFACTURER_CODE)
//			|| (NOR_Id.Device_Code1 != (uint16_t) DEVICE_CODE1)
//			|| (NOR_Id.Device_Code2 != (uint16_t) DEVICE_CODE2)
//			|| (NOR_Id.Device_Code3 != (uint16_t) DEVICE_CODE3)) {
//		/* NOR ID not correct */
//		SEGGER_RTT_printf(0, "NOR ID error");
//	}

	/* Return to read mode */
	HAL_NOR_ReturnToReadMode(&hnor1);
	/* Erase the NOR memory block to write on */
	HAL_NOR_Erase_Block(&hnor1, WRITE_READ_ADDR, NOR_BANK_ADDR);
	/* Return the NOR memory status */
	if (HAL_NOR_GetStatus(&hnor1, NOR_BANK_ADDR, NOR_TIMEOUT_VALUE)
			!= HAL_NOR_STATUS_SUCCESS) {
		SEGGER_RTT_printf(0, "NOR status error");
	}
}

void FMC_Write(uint8_t *aTxBuffer) {
	uint8_t *pdata = 0;
	uint32_t index = 0;
	uint32_t startaddress = 0;

	pdata = aTxBuffer;
	index = IMAGE_SIZE;
	startaddress = NOR_BANK_ADDR + WRITE_READ_ADDR;
	while (index > 0) {
		/* Write data to NOR */
		HAL_NOR_Program(&hnor1, (uint32_t*) startaddress, pdata);
		/* Read NOR device status */
		if (HAL_NOR_GetStatus(&hnor1, NOR_BANK_ADDR, NOR_TIMEOUT_VALUE)
				!= HAL_NOR_STATUS_SUCCESS) {
			SEGGER_RTT_printf(0, "NOR status error");
		}

		index--;
		startaddress += 2;
		pdata++;

	}

}

void FMC_Read(void) {
	HAL_DMA_Start(&hdma_memtomem_dma1_channel1,
			(uint32_t) 0x64000000 + (uint32_t) 0x8000, aRxBuffer, IMAGE_SIZE);

}

