/*
 * dcmi_driver.cpp
 *
 *  Created on: Aug 15, 2019
 *      Author: duyanhpham
 */

#include "dcmi_driver.h"
#include "../SEGGER/RTT/SEGGER_RTT.h"

// CAMERA_DrvTypeDef *camera;

static uint32_t current_resolution;

/**
 * @brief  Initializes the camera with defauft configurations.
 * @param  Resolution: Camera Resolution
 * @retval Camera status
 */
Camera_StatusTypeDef DCMI_Driver::CAMERA_Init(uint32_t Resolution) {
  Camera_StatusTypeDef ret = CAMERA_ERROR;

  /* DCMI Initialization */
  HAL_DCMI_Init(&hdcmi);

  if (ov2640_ReadID(CAMERA_OV2640_I2C_ADDRESS) == OV2640_ID) {
    /* Initialize the camera driver structure */
    camera = &ov2640_drv;

    /* Camera Init */
    camera->Init(CAMERA_OV2640_I2C_ADDRESS, Resolution);

    /* specific default settings */
    if (IMAGE_BANDFILTER_ENABLE) {
      CAMERA_writeRegValue(DSP_CTRL_REG, 0x13, 0xc5); // activate band filter
    } else {
      CAMERA_writeRegValue(DSP_CTRL_REG, 0x13, 0xe5); // deactivate band
    }
    CAMERA_setOutputFormat(IMAGE_DEFAULT_FORMAT);
    CAMERA_BlackWhiteConfig(CAMERA_DEFAULT_COLORMODE);

    current_resolution = Resolution;

    /* Return CAMERA_OK status */
    ret = CAMERA_OK;
  } else {
#ifdef CAMERA_DEBUG_RTT
    SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                      "Error: Can't read sensor ID (check sensor ID or I2c "
                      "connection again)\n");
#endif
  }

  camera_status = ret;
#ifdef CAMERA_DEBUG_RTT
  if (camera_status == CAMERA_ERROR) {
    SEGGER_RTT_printf(
        CAMERA_COMMON_DEBUG_RTT_DISABLE,
        "-------------Error: CAMERA cannot initialized------------------\n");
  } else {
    SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                      "----------------CAMERA INIT OK-------------\n");
  }
#endif
  return ret;
}

/**
 * @brief  Initializes the camera hardware
 */
void DCMI_Driver::CAMERA_MsInit(void) { HAL_DCMI_MspInit(&hdcmi); }

// TODO: test video capture
/**
 * @brief  Starts the camera capture in continuous mode.
 * @param  buff: pointer to the camera output buffer
 */
void DCMI_Driver::CAMERA_ContinuousStart(uint8_t *buff) {
  /* Start the camera capture */
  HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)buff,
                     GetSize(current_resolution));
}

/**
 * @brief  Starts the camera capture in snapshot mode.
 * @param  buff: pointer to the camera output buffer
 */
void DCMI_Driver::CAMERA_SnapshotStart(uint8_t *buff) {
  /* Start the camera capture */
  lineNum = 0;
  __HAL_DCMI_ENABLE_IT(&hdcmi, DCMI_IT_FRAME | DCMI_IT_LINE | DCMI_IT_VSYNC);
#ifdef CAMERA_DEBUG_RTT
  SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                    "Starting camera... (delay for %d ms)\n",
                    CAMERA_DELAY_INTERVAL);
  CAMERA_Delay(CAMERA_DELAY_INTERVAL);
  SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                    "Start taking a snapshot image\n");
#endif
  HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT, (uint32_t)buff,
                     GetSize(current_resolution));
}

// TODO: test suspend
/**
 * @brief Suspend the CAMERA capture
 */
void DCMI_Driver::CAMERA_Suspend(void) {
  /* Suspend the Camera Capture */
  HAL_DCMI_Suspend(&hdcmi);
}

// TODO: test resume
/**
 * @brief Resume the CAMERA capture
 */
void DCMI_Driver::CAMERA_Resume(void) {
  /* Start the Camera Capture */
  HAL_DCMI_Resume(&hdcmi);
}

/**
 * @brief  Stop the CAMERA capture
 * @retval Camera status
 */
Camera_StatusTypeDef DCMI_Driver::CAMERA_Stop(void) {
  DCMI_HandleTypeDef *phdcmi;

  Camera_StatusTypeDef ret = CAMERA_ERROR;

  /* Get the DCMI handle structure */
  phdcmi = &hdcmi;

  if (HAL_DCMI_Stop(phdcmi) == HAL_OK) {
    ret = CAMERA_OK;
  }

  // TODO: make a camera on/off switch

  camera_status = ret;
#ifdef CAMERA_DEBUG_RTT
  if (camera_status == CAMERA_ERROR) {
    SEGGER_RTT_printf(
        CAMERA_COMMON_DEBUG_RTT_DISABLE,
        "-------------Error: CAMERA cannot initialized------------------\n");
  } else {
    SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                      "----------------CAMERA INIT OK-------------\n");
  }
#endif
  return ret;
}

/**
 * @brief Get capture size (in words)
 * @param Resolution
 * 		   Posible Value
 * 		     @arg CAMERA_R160x120
 * 		     @arg CAMERA_R320x240
 * 		     @arg CAMERA_R480x272
 * 		     @arg CAMERA_R640x480
 */
uint32_t DCMI_Driver::GetSize(uint32_t resolution) {
  uint32_t size = 0;

  /* Get capture size */
  switch (resolution) {
  case CAMERA_R160x120: {
    size = 0x2580;
  } break;
  case CAMERA_R320x240: {
    size = 0x9600;
  } break;
  case CAMERA_R480x272: {
    size = 0xFF00;
  } break;
  case CAMERA_R640x480: {
    size = 0x25800;
  } break;
  default: {
    break;
  }
  }

  return size;
}

/**
 * @brief  Configures the camera contrast and brightness.
 * @param  contrast_level: Contrast level
 *          This parameter can be one of the following values:
 *            @arg  CAMERA_CONTRAST_LEVEL4: for contrast +2
 *            @arg  CAMERA_CONTRAST_LEVEL3: for contrast +1
 *            @arg  CAMERA_CONTRAST_LEVEL2: for contrast  0
 *            @arg  CAMERA_CONTRAST_LEVEL1: for contrast -1
 *            @arg  CAMERA_CONTRAST_LEVEL0: for contrast -2
 * @param  brightness_level: Contrast level
 *          This parameter can be one of the following values:
 *            @arg  CAMERA_BRIGHTNESS_LEVEL4: for brightness +2
 *            @arg  CAMERA_BRIGHTNESS_LEVEL3: for brightness +1
 *            @arg  CAMERA_BRIGHTNESS_LEVEL2: for brightness  0
 *            @arg  CAMERA_BRIGHTNESS_LEVEL1: for brightness -1
 *            @arg  CAMERA_BRIGHTNESS_LEVEL0: for brightness -2
 */
void DCMI_Driver::CAMERA_ContrastBrightnessConfig(uint32_t contrast_level,
                                                  uint32_t brightness_level) {
  if (camera->Config != NULL) {
    camera->Config(CAMERA_OV2640_I2C_ADDRESS, CAMERA_CONTRAST_BRIGHTNESS,
                   contrast_level, brightness_level);
  }
}

/**
 * @brief  Configures the camera white balance.
 * @param  Mode: black_white mode
 *          This parameter can be one of the following values:
 *            @arg  CAMERA_BLACK_WHITE_BW
 *            @arg  CAMERA_BLACK_WHITE_NEGATIVE
 *            @arg  CAMERA_BLACK_WHITE_BW_NEGATIVE
 *            @arg  CAMERA_BLACK_WHITE_NORMAL
 */
void DCMI_Driver::CAMERA_BlackWhiteConfig(uint32_t Mode) {
  if (camera->Config != NULL) {
    camera->Config(CAMERA_OV2640_I2C_ADDRESS, CAMERA_BLACK_WHITE, Mode, 0);
  }
}

/**
 * @brief  Configures the camera color effect.
 * @param  Effect: Color effect
 *          This parameter can be one of the following values:
 *            @arg  CAMERA_COLOR_EFFECT_ANTIQUE
 *            @arg  CAMERA_COLOR_EFFECT_BLUE
 *            @arg  CAMERA_COLOR_EFFECT_GREEN
 *            @arg  CAMERA_COLOR_EFFECT_RED
 */
void DCMI_Driver::CAMERA_ColorEffectConfig(uint32_t Effect) {
  if (camera->Config != NULL) {
    camera->Config(CAMERA_OV2640_I2C_ADDRESS, CAMERA_COLOR_EFFECT, Effect, 0);
  }
}

/**
 * @brief  Line event callback
 * @param  hdcmi: pointer to the DCMI handle
 */
void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi) {
  DCMI_Driver::instance().CAMERA_LineEventCallback();
}

/**
 * @brief  VSYNC event callback
 * @param  hdcmi: pointer to the DCMI handle
 */
void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi) {
  DCMI_Driver::instance().CAMERA_VsyncEventCallback();
}

/**
 * @brief  Frame event callback
 * @param  hdcmi: pointer to the DCMI handle
 */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) {
  DCMI_Driver::instance().CAMERA_FrameEventCallback();
}

/**
 * @brief  Error callback
 * @param  hdcmi: pointer to the DCMI handle
 */
void HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi) {
  DCMI_Driver::instance().CAMERA_ErrorCallback();
}

/**
 * @brief  Handles DCMI interrupt request.
 */
void DCMI_Driver::CAMERA_IRQHandler(void) { HAL_DCMI_IRQHandler(&hdcmi); }

/**
 * @brief  Handles DMA interrupt request.
 */
void DCMI_Driver::CAMERA_DMA_IRQHandler(void) {
  HAL_DMA_IRQHandler(hdcmi.DMA_Handle);
}

/**
 * @brief  Read Register value
 * @param  REG_ADDRESS: register address
 */
uint8_t DCMI_Driver::CAMERA_readRegValue(uint8_t REG_ADDRESS) {
  uint8_t tmp = CAMERA_IO_Read(OV2640_I2C_ADDRESS, REG_ADDRESS);
  CAMERA_Delay(1);
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
void DCMI_Driver::CAMERA_writeRegValue(bool REG_BANK_SEL, uint8_t REG_ADDRESS,
                                       uint8_t VALUE) {
  if (REG_BANK_SEL == SENSOR_CTRL_REG) {
    CAMERA_IO_Write(OV2640_I2C_ADDRESS, OV2640_DSP_RA_DLMT,
                    OV2640_RDSP_RA_DLMT_SEL_SENSOR);
  } else if (REG_BANK_SEL == DSP_CTRL_REG) {
    CAMERA_IO_Write(OV2640_I2C_ADDRESS, OV2640_DSP_RA_DLMT,
                    OV2640_RDSP_RA_DLMT_SEL_DSP);
  }
  CAMERA_Delay(1);
  CAMERA_IO_Write(OV2640_I2C_ADDRESS, REG_ADDRESS, VALUE);
  CAMERA_Delay(1);
}

/** @brief write control signal to camera module (for camera module with only 1
 * register bank, e.g. OV9655)
 * registers, false when choosing DSP register @param REG_ADDRESS @param VALUE
 */
void DCMI_Driver::CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE) {
  CAMERA_Delay(1);
  CAMERA_IO_Write(OV2640_I2C_ADDRESS, REG_ADDRESS, VALUE);
  CAMERA_Delay(1);
}

/**
 * @brief factory reset all camera register
 */
void DCMI_Driver::CAMERA_factoryReset(void) {
  CAMERA_IO_Write(CAMERA_OV2640_I2C_ADDRESS, OV2640_DSP_RA_DLMT,
                  OV2640_RDSP_RA_DLMT_SEL_DSP);
  CAMERA_Delay(1);
  CAMERA_writeRegValue(SENSOR_CTRL_REG, OV2640_SENSOR_COM7,
                       0x80); // reset all registers
  CAMERA_Delay(1);
}

void DCMI_Driver::CAMERA_setOutputFormat(uint8_t format) {
  switch (format) {
  case IMAGE_OUTPUT_FORMAT_JPEG:
    // TODO: JPEG
    break;
  case IMAGE_OUTPUT_FORMAT_RAW10:
    CAMERA_writeRegValue(DSP_CTRL_REG, OV2640_DSP_IMAGE_MODE,
                         0x04); // enable RAW10-format
    break;
  case IMAGE_OUTPUT_FORMAT_RBG565:
    CAMERA_writeRegValue(DSP_CTRL_REG, OV2640_DSP_IMAGE_MODE,
                         0x08); // enable RGB565-format
    break;
  case IMAGE_OUTPUT_FORMAT_YUV422:
    CAMERA_writeRegValue(DSP_CTRL_REG, OV2640_DSP_IMAGE_MODE,
                         0x01); // enable YCBCR-format
    break;
  default:
    break;
  }
};

void DCMI_Driver::CAMERA_LineEventCallback(void) {
  __HAL_DCMI_CLEAR_FLAG(&hdcmi, DCMI_IT_LINE);
  lineNum++;
#ifdef CAMERA_DEBUG_RTT
  SEGGER_RTT_printf(CAMERA_EVENT_DEBUG_RTT_DISABLE, "End of line %d event \n",
                    lineNum);
#endif
}
void DCMI_Driver::CAMERA_VsyncEventCallback(void) {
  __HAL_DCMI_CLEAR_FLAG(&hdcmi, DCMI_IT_VSYNC);
#ifdef CAMERA_DEBUG_RTT
  SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                    "Vsync event - sychronization frame\n");
  SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE, "--Total line read: %d\n",
                    lineNum);
#endif
  lineNum = 0;
  // TODO: send image over UART for preview in pc
}
void DCMI_Driver::CAMERA_FrameEventCallback(void) {
  __HAL_DCMI_CLEAR_FLAG(&hdcmi, DCMI_IT_FRAME);
  HAL_UART_Transmit_IT(&huart5, CAMERA_BUFFER, IMAGE_SIZE);
#ifdef CAMERA_DEBUG_RTT
  SEGGER_RTT_printf(CAMERA_EVENT_DEBUG_RTT_DISABLE, "Frame captured event\n");
  SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                    "Frame captured, sending image...\n");
#endif
}
void DCMI_Driver::CAMERA_ErrorCallback(void) {
#ifdef CAMERA_DEBUG_RTT
  SEGGER_RTT_printf(CAMERA_EVENT_DEBUG_RTT_DISABLE,
                    "ERROR: Frame synchonization error event\n");
#endif
}
