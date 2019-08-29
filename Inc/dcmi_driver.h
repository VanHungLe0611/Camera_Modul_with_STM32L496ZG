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

#include "i2c_driver.h"
#include "ov2640.h"
#include "stm32l4xx_hal.h"

#define DSP_CTRL_REG 0x00
#define SENSOR_CTRL_REG 0x01

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

class DCMI_Driver {
private:
  DCMI_Driver() { camera_status = CAMERA_ERROR; }
  DCMI_Driver(const DCMI_Driver &);
  DCMI_Driver &operator=(const DCMI_Driver &);
  CAMERA_DrvTypeDef *camera;
  Camera_StatusTypeDef camera_status;
  uint16_t camera_i2c_addr;

public:
  static DCMI_Driver &instance() {
    static DCMI_Driver _instance;
    return _instance;
  }
  ~DCMI_Driver() {}
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
  void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState);

  /* To be called in DCMI_IRQHandler function */
  void CAMERA_IRQHandler(void);
  /* To be called in DMA2_Stream1_IRQHandler function */
  void CAMERA_DMA_IRQHandler(void);

  /* utilities function */
  uint32_t GetSize(uint32_t resolution);
  uint8_t CAMERA_readRegValue(uint8_t REG_ADDRESS);
  void CAMERA_writeRegValue(bool REG_BANK_SEL, uint8_t REG_ADDRESS,
                            uint8_t VALUE);
  void CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE);

  /* HAL Function override */
};

#ifdef __cplusplus
}
#endif

#endif /* INC_DCMI_DRIVER_H_ */
