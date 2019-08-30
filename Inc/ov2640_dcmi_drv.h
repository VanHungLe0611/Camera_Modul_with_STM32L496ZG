/*
 * dcmi_driver.h
 *
 *  Created on: Aug 15, 2019
 *      Author: duyanhpham
 */

#ifndef INC_DCMI_DRIVER_H_
#define INC_DCMI_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dcmi_driver_interface.h"
#include "i2c_driver.h"
#include "ov2640.h"

#define CAMERA_OV2640_I2C_ADDRESS 0x60
#define DSP_CTRL_REG 0x00
#define SENSOR_CTRL_REG 0x01

class ov2640_dcmi_drv : DCMI_Driver_interface {
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
  void CAMERA_MsInit(void);
  Camera_StatusTypeDef CAMERA_Init(uint32_t Resolution);
  void CAMERA_ContinuousStart(uint8_t *buff);
  void CAMERA_SnapshotStart(uint8_t *buff);
  void CAMERA_Suspend(void);
  void CAMERA_Resume(void);
  Camera_StatusTypeDef CAMERA_Stop(void);
  /* Camera features functions prototype */
  void CAMERA_ContrastBrightnessConfig(uint32_t contrast_level,
                                       uint32_t brightness_level);
  void CAMERA_BlackWhiteConfig(uint32_t Mode);
  void CAMERA_ColorEffectConfig(uint32_t Effect);
  void CAMERA_factoryReset(void);
  void CAMERA_setOutputFormat(uint8_t format);
  /* Camera interrupts and callbacks functions */
  void CAMERA_LineEventCallback(void);
  void CAMERA_VsyncEventCallback(void);
  void CAMERA_FrameEventCallback(void);
  void CAMERA_ErrorCallback(void);

  /* To be called in DCMI_IRQHandler function */
  void CAMERA_IRQHandler(void);
  /* To be called in DMA2_Stream1_IRQHandler function */
  void CAMERA_DMA_IRQHandler(void);

  /* utilities function */
  uint32_t GetSize(uint32_t resolution);
  uint8_t CAMERA_readRegValue(uint8_t REG_ADDRESS);
  void CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE);

  /* HAL Function override */
};

#ifdef __cplusplus
}
#endif

#endif /* INC_DCMI_DRIVER_H_ */
