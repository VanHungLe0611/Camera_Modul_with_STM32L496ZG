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
#include "ov2640.h"

#define CAMERA_OV2640_I2C_ADDRESS 0x60
#define DSP_CTRL_REG 0x00
#define SENSOR_CTRL_REG 0x01

class ov2640_dcmi_drv : public DCMI_Driver{
private:
  ov2640_dcmi_drv() {
    camera_status = CAMERA_ERROR;
    camera_i2c_addr = CAMERA_OV2640_I2C_ADDRESS;
  }
  ov2640_dcmi_drv(const ov2640_dcmi_drv &);
  ov2640_dcmi_drv &operator=(const ov2640_dcmi_drv &);
  void CAMERA_writeRegValue(bool REG_BANK_SEL, uint8_t REG_ADDRESS,
                            uint8_t VALUE);

public:
  static ov2640_dcmi_drv &instance() {
    static ov2640_dcmi_drv _instance;
    return _instance;
  }
  ~ov2640_dcmi_drv() {}
  
  /* Camera sensor initialization */
  Camera_StatusTypeDef CAMERA_Init(uint32_t Resolution);

  /* Sensor control */
  void CAMERA_ContrastBrightnessConfig(uint32_t contrast_level,
                                       uint32_t brightness_level);
  void CAMERA_BlackWhiteConfig(uint32_t Mode);
  void CAMERA_ColorEffectConfig(uint32_t Effect);
  void CAMERA_factoryReset(void);
  void CAMERA_setOutputFormat(uint8_t format);

  /* Register control */
  uint8_t CAMERA_readRegValue(uint8_t REG_ADDRESS);
  void CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE);

  /* HAL Function override */
};

#ifdef __cplusplus
}
#endif

#endif /* INC_OV2640_DCMI_DRV_H_ */
