/*
 * dcmi_driver_interface.h
 *
 *  Created on: Aug 29, 2019
 *      Author: duyanhpham
 */

#ifndef INC_DCMI_DRIVER_H_
#define INC_DCMI_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "SEGGER_RTT.h"
#include "camera.h"
#include "stm32l4xx_hal.h"
#include "var_interface.h"

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

/* START DCMI_Driver class*/
class DCMI_Driver {
protected:
  CAMERA_DrvTypeDef *camera;
  Camera_StatusTypeDef camera_status;
  uint16_t camera_i2c_addr;
  uint32_t current_resolution;

public:
  /*
   *--------------------- DCMI common functions-------------------------------
   */
  /* Hardware initialization */
  void CAMERA_MsInit(void);

  /* Camera common operations */
  void CAMERA_ContinuousStart(uint8_t *buff);
  void CAMERA_SnapshotStart(uint8_t *buff);
  void CAMERA_Suspend(void);
  void CAMERA_Resume(void);
  Camera_StatusTypeDef CAMERA_Stop(void);

  /* Camera interrupts handler and callbacks functions */
  static void CAMERA_LineEventCallback(void);
  static void CAMERA_VsyncEventCallback(void);
  static void CAMERA_FrameEventCallback(void);
  static void CAMERA_ErrorCallback(void);

  void CAMERA_IRQHandler(void);
  void CAMERA_DMA_IRQHandler(void);

  void  uart_transmit_complete(void);
  void  HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

  uint32_t GetSize(uint32_t resolution);

  /*
   *----------------- interface functions for sensor--------------------------
   */
  /* Camera sensor initialization */
  virtual Camera_StatusTypeDef CAMERA_Init(uint32_t Resolution) = 0;

  /* Register control */
  virtual uint8_t CAMERA_readRegValue(uint8_t REG_ADDRESS) = 0;
  virtual void CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE) = 0;

  /* Sensor control */
  virtual void CAMERA_ContrastBrightnessConfig(uint32_t contrast_level,
                                               uint32_t brightness_level) = 0;
  virtual void CAMERA_BlackWhiteConfig(uint32_t Mode) = 0;
  virtual void CAMERA_ColorEffectConfig(uint32_t Effect) = 0;
  virtual void CAMERA_factoryReset(void) = 0;
  virtual void CAMERA_setOutputFormat(uint8_t format) = 0;
};
/* END  DCMI_Driver class*/


#ifdef __cplusplus
}
#endif

#endif /* INC_DCMI_DRIVER_H_ */
