/*
 * dcmi_driver.cpp
 *
 *  Created on: Aug 15, 2019
 *      Author: duyanhpham
 */

#include "ov2640_dcmi_drv.h"
#include "../SEGGER/RTT/SEGGER_RTT.h"

// CAMERA_DrvTypeDef *camera;

/**
 * @brief  Initializes the camera with defauft configurations.
 * @param  Resolution: Camera Resolution
 * @retval Camera status
 */
Camera_StatusTypeDef ov2640_dcmi_drv::CAMERA_Init(uint32_t Resolution) {
  Camera_StatusTypeDef ret = CAMERA_ERROR;

  /* DCMI Initialization */
  // HAL_DCMI_Init(&hdcmi); //TODO: do we need this?

  if (ov2640_ReadID(camera_i2c_addr) == OV2640_ID) {
    /* Initialize the camera driver structure */
    camera = &ov2640_drv;

    /* Camera Init */
    camera->Init(camera_i2c_addr, Resolution);

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
        "-----------Error: CAMERA cannot initialized correctly----------\n");
  } else {
    SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                      "----------------CAMERA INIT OK-------------\n");
  }
  SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
                    "Starting camera... (delay for %d ms)\n",
                    CAMERA_DELAY_INTERVAL);
  SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE, "Done\n");
  CAMERA_Delay(CAMERA_DELAY_INTERVAL);
#endif
  return ret;
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
void ov2640_dcmi_drv::CAMERA_ContrastBrightnessConfig(
    uint32_t contrast_level, uint32_t brightness_level) {
  if (camera->Config != NULL) {
    camera->Config(camera_i2c_addr, CAMERA_CONTRAST_BRIGHTNESS, contrast_level,
                   brightness_level);
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
void ov2640_dcmi_drv::CAMERA_BlackWhiteConfig(uint32_t Mode) {
  if (camera->Config != NULL) {
    camera->Config(camera_i2c_addr, CAMERA_BLACK_WHITE, Mode, 0);
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
void ov2640_dcmi_drv::CAMERA_ColorEffectConfig(uint32_t Effect) {
  if (camera->Config != NULL) {
    camera->Config(camera_i2c_addr, CAMERA_COLOR_EFFECT, Effect, 0);
  }
}

/**
 * @brief  Read Register value
 * @param  REG_ADDRESS: register address
 */
uint8_t ov2640_dcmi_drv::CAMERA_readRegValue(uint8_t REG_ADDRESS) {
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
void ov2640_dcmi_drv::CAMERA_writeRegValue(bool REG_BANK_SEL,
                                           uint8_t REG_ADDRESS, uint8_t VALUE) {
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

/** @brief write control signal to camera module  registers, false when choosing
 * DSP register
 * @param REG_ADDRESS
 * @param VALUE
 */
void ov2640_dcmi_drv::CAMERA_writeRegValue(uint8_t REG_ADDRESS, uint8_t VALUE) {
  CAMERA_Delay(1);
  CAMERA_IO_Write(OV2640_I2C_ADDRESS, REG_ADDRESS, VALUE);
  CAMERA_Delay(1);
}

/**
 * @brief factory reset all camera register
 */
void ov2640_dcmi_drv::CAMERA_factoryReset(void) {
  CAMERA_IO_Write(camera_i2c_addr, OV2640_DSP_RA_DLMT,
                  OV2640_RDSP_RA_DLMT_SEL_DSP);
  CAMERA_Delay(1);
  CAMERA_writeRegValue(SENSOR_CTRL_REG, OV2640_SENSOR_COM7,
                       0x80); // reset all registers
  CAMERA_Delay(1);
}

void ov2640_dcmi_drv::CAMERA_setOutputFormat(uint8_t format) {
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
