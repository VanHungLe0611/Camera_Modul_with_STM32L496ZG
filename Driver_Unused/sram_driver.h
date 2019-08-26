/*
 * sram_driver.h
 *
 *  Created on: 26.08.2019
 *      Author: hungv
 */

#ifndef INC_SRAM_DRIVER_H_
#define INC_SRAM_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32l4xx.h"
#include "var_interface.h"

#define SRAM_BANK_ADDR ((uint32_t)0x68000000)
/* #define SRAM_MEMORY_WIDTH FMC_NORSRAM_MEM_BUS_WIDTH_8 */
#define SRAM_MEMORY_WIDTH FMC_NORSRAM_MEM_BUS_WIDTH_16
/* #define SRAM_MEMORY_WIDTH FMC_NORSRAM_MEM_BUS_WIDTH_32 */
#define SRAM_TIMEOUT ((uint32_t)0xFFFF)
#define BUFFER_SIZE ((uint32_t)16)
#define WRITE_READ_ADDR ((uint32_t)0x0800)

//static SRAM_HandleTypeDef hsram1;

void SRAM_Write(uint16_t *aTxBuffer);
void SRAM_Read(void);
/**
 * @brief SRAM status definition
 */
#define SRAM_STATUS_OK 0x00
#define SRAM_STATUS_INIT_ERROR 0x01

#ifdef __cplusplus
}
#endif

#endif /* INC_SRAM_DRIVER_H_ */
