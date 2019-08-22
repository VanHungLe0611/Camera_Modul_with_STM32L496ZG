/*
 * fmc_driver.h
 *
 *  Created on: 22.08.2019
 *      Author: hungv
 */

#ifndef INC_FMC_DRIVER_H_
#define INC_FMC_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32l4xx.h"
#include "var_interface.h"

#define NOR_DEVICE_ADDR ((uint32_t)0x64000000)
#define WRITE_READ_ADDR ((uint32_t)0x8000)

#define MANUFACTURER_CODE ((uint16_t)0x0020)
#define DEVICE_CODE1 ((uint16_t)0x227E)
#define DEVICE_CODE2 ((uint16_t)0x2221)
#define DEVICE_CODE3 ((uint16_t)0x2200)

#define NOR_BANK_ADDR ((uint32_t)0x64000000)
#define NOR_TIMEOUT_VALUE ((uint32_t)0xFFFF)

#define NOR_STATUS_OK 0x00
#define NOR_STATUS_INIT_ERROR 0x01
#define NOR_STATUS_READ_ID_ERROR 0x02
#define NOR_STATUS_ID_ERROR 0x03
#define NOR_STATUS_ERASE_ERROR 0x04
#define NOR_STATUS_WRITE_ERROR 0x05
#define NOR_STATUS_READ_ERROR 0x06

static NOR_IDTypeDef NOR_Id;

void FMC_Init_Default(void);
void FMC_Write(uint8_t *aTxBuffer);
void FMC_Read(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_FMC_DRIVER_H_ */
