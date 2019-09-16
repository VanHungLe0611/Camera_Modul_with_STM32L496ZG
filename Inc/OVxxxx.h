/*
 * dcmi_driver.h
 *
 *  Created on: Aug 15, 2019
 *      Author: duyanhpham
 */

#ifndef INC_OVXXXX_H_
#define INC_OVXXXX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "I2C_IO.h"
#include "dwt_stm32_delay.h"


// #define DSP_CTRL_REG 0x00
// #define SENSOR_CTRL_REG 0x01

typedef enum {
  CAMERA_OK = 0x00,
  CAMERA_ERROR = 0x01,
  CAMERA_TIMEOUT = 0x02
} Camera_StatusTypeDef;

class OVxxxx {
protected:
	uint16_t oVAddr;
	uint32_t resolution;
	uint8_t digitalRegBank;
	uint8_t sensorRegBank;
	uint8_t regBankSelectCommand;
	I2C_IO i2c;


public:
	 OVxxxx(){
		oVAddr = 0x00;
		resolution = 0x00;
		digitalRegBank = 0x00;
		sensorRegBank = 0x00;
		regBankSelectCommand  = 0x00;	}

	 virtual ~OVxxxx(){

	 }

	/* Camera sensor initialization */
	virtual Camera_StatusTypeDef init(uint32_t Resolution) = 0;
	/* Sensor control */
	virtual void contrastBrightnessConfig(uint32_t contrast_level,
			uint32_t brightness_level) = 0;
	virtual void blackWhiteConfig(uint32_t Mode) = 0;
	virtual void colorEffectConfig(uint32_t Effect) = 0;
	virtual void factoryReset(void) = 0;
	virtual void setOutputFormat(uint8_t format) = 0;

	/* Register control */
	 uint8_t readRegValue(uint8_t REG_ADDRESS);
	 void writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE);
	 void writeMultipleRegValue(bool REG_BANK_SEL, uint8_t REG_ADDRESS, uint8_t VALUE);

	/* HAL Function override */
};

#ifdef __cplusplus
}
#endif

#endif /* INC_OVXXXX_H_ */
