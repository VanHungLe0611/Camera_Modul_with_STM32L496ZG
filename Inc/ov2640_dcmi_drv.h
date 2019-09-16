/*
 * dcmi_driver.h
 *
 *  Created on: Aug 15, 2019
 *      Author: duyanhpham
 */

#ifndef INC_OV2640_DCMI_DRV_H_
#define INC_OV2640_DCMI_DRV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dcmi_driver.h"
#include "i2c_dcmi_driver.h"


// #define DSP_CTRL_REG 0x00
// #define SENSOR_CTRL_REG 0x01

class ov2640_dcmi_drv {
protected:
	uint16_t camera_i2c_addr;
	uint32_t current_resolution;
	uint8_t digitalRegBank;
	uint8_t sensorRegBank;
	uint8_t regBankSelectCommand;


public:
	 ov2640_dcmi_drv(){
		camera_i2c_addr = 0x00;
		current_resolution = 0x00;
		digitalRegBank = 0x00;
		sensorRegBank = 0x00;
		regBankSelectCommand  = 0x00;
	}

	 virtual ~ov2640_dcmi_drv(){

	 }

	/* Camera sensor initialization */
	virtual Camera_StatusTypeDef CAMERA_Init(uint32_t Resolution) = 0;
	/* Sensor control */
	virtual void CAMERA_ContrastBrightnessConfig(uint32_t contrast_level,
			uint32_t brightness_level) = 0;
	virtual void CAMERA_BlackWhiteConfig(uint32_t Mode) = 0;
	virtual void CAMERA_ColorEffectConfig(uint32_t Effect) = 0;
	virtual void CAMERA_factoryReset(void) = 0;
	virtual void CAMERA_setOutputFormat(uint8_t format) = 0;

	/* Register control */
	 uint8_t CAMERA_readRegValue(uint8_t REG_ADDRESS);
	 void CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE);
	 void CAMERA_writeMultipleRegValue(bool REG_BANK_SEL, uint8_t REG_ADDRESS, uint8_t VALUE);

	/* HAL Function override */
};

#ifdef __cplusplus
}
#endif

#endif /* INC_OV2640_DCMI_DRV_H_ */
