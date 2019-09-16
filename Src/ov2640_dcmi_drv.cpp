/*
 * dcmi_driver.cpp
 *
 *  Created on: Aug 15, 2019
 *      Author: duyanhpham
 */

#include "ov2640_dcmi_drv.h"
#include "../SEGGER/RTT/SEGGER_RTT.h"
#include "stm32l4xx_hal.h"

// CAMERA_DrvTypeDef *camera;



/**
 * @brief  Read Register value
 * @param  REG_ADDRESS: register address
 */
uint8_t ov2640_dcmi_drv::CAMERA_readRegValue(uint8_t REG_ADDRESS) {
  uint8_t tmp = I2Cx_Read(camera_i2c_addr, REG_ADDRESS);
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
void ov2640_dcmi_drv::CAMERA_writeMultipleRegValue(bool REG_BANK_SEL,
                                           uint8_t REG_ADDRESS, uint8_t VALUE) {
  if (REG_BANK_SEL == sensorRegBank) {
    I2Cx_Write(camera_i2c_addr, regBankSelectCommand,
    		sensorRegBank);
  } else {
    I2Cx_Write(camera_i2c_addr, regBankSelectCommand,
                    digitalRegBank);
  }
  DWT_Delay_us(CAMERA_DELAY_INTERVAL);
  I2Cx_Write(camera_i2c_addr, REG_ADDRESS, VALUE);
  DWT_Delay_us(CAMERA_DELAY_INTERVAL);
}

/** @brief write control signal to camera module  registers, false when choosing
 * DSP register
 * @param REG_ADDRESS
 * @param VALUE
 */
void ov2640_dcmi_drv::CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE) {
  //DWT_Delay_us(CAMERA_DELAY_INTERVAL);
  I2Cx_Write(camera_i2c_addr, REG_ADDRESS, VALUE);
  DWT_Delay_us(CAMERA_DELAY_INTERVAL);
}
