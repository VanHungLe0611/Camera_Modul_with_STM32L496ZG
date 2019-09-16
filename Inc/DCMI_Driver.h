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
#include "dwt_stm32_delay.h"



#define COLOR_IMG 0x01
#define MONOC_IMG 0x00


/* START DCMI_Driver class*/
class DCMI_Driver {


public:
  /*
   *--------------------- DCMI common functions-------------------------------
   */
  /* Hardware initialization */
  void CAMERA_MsInit(void);

  /* Camera common operations */
  void CAMERA_ContinuousStart(uint8_t *buff);
  void CAMERA_SnapshotStart(uint8_t imgNum, uint16_t current_resolution);
  void CAMERA_Suspend(void);
  void CAMERA_Resume(void);
  HAL_StatusTypeDef CAMERA_Stop(void);

  /* Camera interrupts handler and callbacks functions */
  static void CAMERA_LineEventCallback(void);
  static void CAMERA_VsyncEventCallback(void);
  static void CAMERA_FrameEventCallback(void);
  static void CAMERA_ErrorCallback(void);

  void CAMERA_IRQHandler(void);
  void CAMERA_DMA_IRQHandler(void);

  void  uart_transmit_complete(void);
  void  HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

  uint32_t GetSizeInWord(uint32_t resolution);
  uint32_t GetSizeInByte(uint32_t resolution, uint8_t color);

};
/* END  DCMI_Driver class*/


#ifdef __cplusplus
}
#endif

#endif /* INC_DCMI_DRIVER_H_ */
