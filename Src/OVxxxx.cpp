/*
 * dcmi_driver.cpp
 *
 *  Created on: Aug 15, 2019
 *      Author: duyanhpham
 */

#include "OVxxxx.h"


// CAMERA_DrvTypeDef *camera;



/**
 * @brief  Read Register value
 * @param  REG_ADDRESS: register address
 */
uint8_t OVxxxx::readRegValue(uint8_t REG_ADDRESS) {
  uint8_t tmp = i2c.read(oVAddr, REG_ADDRESS);
  DWT_Delay_us(CAMERA_DELAY_INTERVAL);
  return tmp;
}

/**
 * @brief write control signal to camera module (for camera module with multiple
 * bank register, e.g. OV2640)
 * @param REG_BANK_SEL true when choosing sensor registers, false when choosing
 * DSP register
 * @param REG_ADDRESS
 * @param VALUE
 */
void OVxxxx::writeMultipleRegValue(bool REG_BANK_SEL,
                                           uint8_t REG_ADDRESS, uint8_t VALUE) {
  if (REG_BANK_SEL == sensorRegBank) {
	  i2c.write(oVAddr, regBankSelectCommand,
    		sensorRegBank);
  } else {
	  i2c.write(oVAddr, regBankSelectCommand,
                    digitalRegBank);
  }
  DWT_Delay_us(CAMERA_DELAY_INTERVAL);
  i2c.write(oVAddr, REG_ADDRESS, VALUE);
  DWT_Delay_us(CAMERA_DELAY_INTERVAL);
}

/** @brief write control signal to camera module  registers, false when choosing
 * DSP register
 * @param REG_ADDRESS
 * @param VALUE
 */
void OVxxxx::writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE) {
  //DWT_Delay_us(CAMERA_DELAY_INTERVAL);
	i2c.write(oVAddr, REG_ADDRESS, VALUE);
  DWT_Delay_us(CAMERA_DELAY_INTERVAL);
}
