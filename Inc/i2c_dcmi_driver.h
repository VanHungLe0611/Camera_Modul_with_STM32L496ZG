#ifndef __I2C_DCMI_DRIVER_H
#define __I2C_DCMI_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"
#include "var_interface.h"

/**
 * @brief  Define for STM324x9I_EVAL board
 */
#if !defined(USE_STM324x9I_EVAL)
#define USE_STM324x9I_EVAL
#endif

void I2Cx_Init();
void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg);
HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg,
		uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg,
		uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
void I2Cx_Error(uint8_t Addr);

#ifdef __cplusplus
}
#endif

#endif /* INC_I2C_DCMI_DRIVER_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
