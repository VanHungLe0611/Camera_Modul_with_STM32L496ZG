#ifndef __I2C_DCMI_DRIVER_H
#define __I2C_DCMI_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"
#include "var_interface.h"
#include "SEGGER_RTT.h"

/**
 * @brief  Define for STM324x9I_EVAL board
 */

class I2C_IO{
protected :
	I2C_HandleTypeDef * pI2C;
public:
	I2C_IO(){
		pI2C =  NULL;
	}


void init(I2C_HandleTypeDef * pi2c);
HAL_StatusTypeDef write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t read(uint8_t Addr, uint8_t Reg);
HAL_StatusTypeDef readMultiple(uint8_t Addr, uint16_t Reg,
		uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
HAL_StatusTypeDef writeMultiple(uint8_t Addr, uint16_t Reg,
		uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
void errorHandle(uint8_t Addr);

~I2C_IO(){

	}
};
#ifdef __cplusplus
}
#endif

#endif /* INC_I2C_DCMI_DRIVER_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
