#include "i2c_dcmi_driver.h"

static I2C_HandleTypeDef *hi2c_dcmi;
// TODO: read/write should do multiple try if I2c error happens
/******************************* I2C Routines *********************************/
/**
 * @brief  Initializes I2C HAL.
 */
void I2Cx_Init() {
	hi2c_dcmi = &hi2c1;
	HAL_I2C_Init(hi2c_dcmi);
}

/**
 * @brief  Writes a single data.
 * @param  Addr: I2C address
 * @param  Reg: Register address
 * @param  Value: Data to be written
 */
void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value) {
	HAL_StatusTypeDef status = HAL_OK;
#ifdef CAMERA_DEBUG_RTT
	SEGGER_RTT_printf(CAMERA_I2C_DEBUG_RTT_DISABLE,
			"I2c write register 0x%x of device 0x%x with value 0x%x\n", Reg,
			Addr, Value);
#endif

	status = HAL_I2C_Mem_Write(hi2c_dcmi, Addr, (uint16_t) Reg,
	I2C_MEMADD_SIZE_8BIT, &Value, 1, 100);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* Execute user timeout callback */
		I2Cx_Error(Addr);
	}
}

/**
 * @brief  Reads a single data.
 * @param  Addr: I2C address
 * @param  Reg: Register address
 * @retval Read data
 */
uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg) {
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t Value = 0;

	status = HAL_I2C_Mem_Read(hi2c_dcmi, Addr, Reg, I2C_MEMADD_SIZE_8BIT,
			&Value, 1, 1000);
#ifdef CAMERA_DEBUG_RTT
	SEGGER_RTT_printf(CAMERA_I2C_DEBUG_RTT_DISABLE,
			"I2c read register 0x%x of device 0x%x\n", Reg, Addr);
#endif
	/* Check the communication status */
	if (status != HAL_OK) {
		/* Execute user timeout callback */
		I2Cx_Error(Addr);
	}
	return Value;
}

/**
 * @brief  Reads multiple data.
 * @param  Addr: I2C address
 * @param  Reg: Reg address
 * @param  MemAddress: Internal memory address
 * @param  Buffer: Pointer to data buffer
 * @param  Length: Length of the data
 * @retval Number of read data
 */
HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg,
		uint16_t MemAddress, uint8_t *Buffer, uint16_t Length) {
	HAL_StatusTypeDef status = HAL_OK;

#ifdef CAMERA_DEBUG_RTT
	SEGGER_RTT_printf(CAMERA_I2C_DEBUG_RTT_DISABLE,
			"I2c read multiple: read register 0x%x of device 0x%x - "
					"sum address: 0x%x\n", Reg, Addr, MemAddress);
#endif
	status = HAL_I2C_Mem_Read(hi2c_dcmi, Addr, (uint16_t) Reg, MemAddress,
			Buffer, Length, 1000);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* I2C error occured */
		I2Cx_Error(Addr);
	}
	return status;
}

/**
 * @brief  Writes a value in a register of the device through BUS in using DMA
 * mode.
 * @param  Addr: Device address on BUS Bus.
 * @param  Reg: The target register address to write
 * @param  MemAddress: Internal memory address
 * @param  Buffer: The target register value to be written
 * @param  Length: buffer size to be written
 * @retval HAL status
 */
HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg,
		uint16_t MemAddress, uint8_t *Buffer, uint16_t Length) {
	HAL_StatusTypeDef status = HAL_OK;
#ifdef CAMERA_DEBUG_RTT
	SEGGER_RTT_printf(CAMERA_I2C_DEBUG_RTT_DISABLE,
			"I2c write multiple: write register 0x%x of device 0x%x - "
					"sum address: 0x%x\n", Reg, Addr, MemAddress);
#endif

	status = HAL_I2C_Mem_Write(hi2c_dcmi, Addr, (uint16_t) Reg, MemAddress,
			Buffer, Length, 1000);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* Re-Initialize the I2C Bus */
		I2Cx_Error(Addr);
	}
	return status;
}

/**
 * @brief  Manages error callback by re-initializing I2C.
 * @param  Addr: I2C Address
 */
void I2Cx_Error(uint8_t Addr) {
#ifdef CAMERA_DEBUG_RTT
	SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
			"Error: I2C HAL Problem \n");
	SEGGER_RTT_printf(
	CAMERA_COMMON_DEBUG_RTT_DISABLE, "--Device at address 0x%x not respond\n",
			Addr);
	SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
			"Reinitializing I2c... ");
#endif
	/* De-initialize the I2C communication bus */
	HAL_I2C_DeInit(hi2c_dcmi);

	/* Re-Initialize the I2C communication bus */
	I2Cx_Init();
#ifdef CAMERA_DEBUG_RTT
	SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE, "Done\n");
#endif
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
