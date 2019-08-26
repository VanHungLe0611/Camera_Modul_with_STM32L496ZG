/*
 * sram_driver.c
 *
 *  Created on: 26.08.2019
 *      Author: hungv
 */

#include "stm32l496xx.h"
#include "sram_driver.h"
#include "var_interface.h"

//uint16_t aTxBuffer[BUFFER_SIZE] = { 0x10, 0x11, 0x02, 0x03, 0x04, 0x05, 0x06,
//		0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
uint16_t aRxBuffer[BUFFER_SIZE] = { 0 };
/* Counter index */
uint32_t uwIndex = 0;
uint32_t length = 16;

void SRAM_Write(uint16_t *aTxBuffer) {

	HAL_DMA_Start_IT(&hdma_memtomem_dma1_channel1, (uint32_t) aTxBuffer,
			(uint32_t) (0x68000800), length);
//
//	for (uwIndex = 0; uwIndex < BUFFER_SIZE; uwIndex++) {
//		*(__IO uint16_t*) (SRAM_BANK_ADDR + WRITE_READ_ADDR + 2 * uwIndex) =
//				aTxBuffer[uwIndex];
//	}
}

void SRAM_Read(void) {
	for (uwIndex = 0; uwIndex < BUFFER_SIZE; uwIndex++) {
		aRxBuffer[uwIndex] = *(__IO uint16_t*) (SRAM_BANK_ADDR +
		WRITE_READ_ADDR + 2 * uwIndex);

	}
}

