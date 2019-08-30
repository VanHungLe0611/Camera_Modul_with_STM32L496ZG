/*
 * dcmi_driver_interface.h
 *
 *  Created on: Aug 29, 2019
 *      Author: duyanhpham
 */

#ifndef INC_DCMI_DRIVER_INTERFACE_H_
#define INC_DCMI_DRIVER_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"
#include "camera.h"

/* Macro for CAMERA_read-/writeRegVal functions */
#define IMAGE_OUTPUT_FORMAT_YUV422 0x00
#define IMAGE_OUTPUT_FORMAT_RAW10 0x01
#define IMAGE_OUTPUT_FORMAT_RBG565 0x02
#define IMAGE_OUTPUT_FORMAT_JPEG 0x03

typedef enum {
  CAMERA_OK = 0x00,
  CAMERA_ERROR = 0x01,
  CAMERA_TIMEOUT = 0x02
} Camera_StatusTypeDef;

class DCMI_Driver_interface {
protected:
  CAMERA_DrvTypeDef *camera;
  Camera_StatusTypeDef camera_status;
  uint16_t camera_i2c_addr;

public:
  virtual void CAMERA_MsInit(void) = 0;
  virtual Camera_StatusTypeDef CAMERA_Init(uint32_t Resolution) = 0;
  virtual void CAMERA_ContinuousStart(uint8_t *buff) = 0;
  virtual void CAMERA_SnapshotStart(uint8_t *buff) = 0;
  virtual void CAMERA_Suspend(void) = 0;
  virtual void CAMERA_Resume(void) = 0;
  virtual Camera_StatusTypeDef CAMERA_Stop(void) = 0;
  /* Camera features functions prototype */
  virtual void CAMERA_ContrastBrightnessConfig(uint32_t contrast_level,
                                               uint32_t brightness_level) = 0;
  virtual void CAMERA_BlackWhiteConfig(uint32_t Mode) = 0;
  virtual void CAMERA_ColorEffectConfig(uint32_t Effect) = 0;
  virtual void CAMERA_factoryReset(void) = 0;
  virtual void CAMERA_setOutputFormat(uint8_t format) = 0;
  /* Camera interrupts and callbacks functions */
  virtual void CAMERA_LineEventCallback(void) = 0;
  virtual void CAMERA_VsyncEventCallback(void) = 0;
  virtual void CAMERA_FrameEventCallback(void) = 0;
  virtual void CAMERA_ErrorCallback(void) = 0;

  /* To be called in DCMI_IRQHandler function */
  virtual void CAMERA_IRQHandler(void) = 0;
  /* To be called in DMA2_Stream1_IRQHandler function */
  virtual void CAMERA_DMA_IRQHandler(void) = 0;

  /* utilities function */
  virtual uint32_t GetSize(uint32_t resolution) = 0;
  virtual uint8_t CAMERA_readRegValue(uint8_t REG_ADDRESS) = 0;
  virtual void CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE) = 0;
};

#ifdef __cplusplus
}
#endif

#endif /* INC_DCMI_DRIVER_INTERFACE_H_ */
