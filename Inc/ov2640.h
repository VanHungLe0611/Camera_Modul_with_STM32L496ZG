/**
 ******************************************************************************
 * @file    ov2640.h
 * @author  MCD Application Team
 * @version V1.0.2
 * @date    02-December-2014
 * @brief   This file contains all the functions prototypes for the ov2640.c
 *          driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *notice, this list of conditions and the following disclaimer in the
 *documentation and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OV2640_H
#define __OV2640_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "camera.h"
#include "stm32l4xx_hal.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @addtogroup ov2640
 * @{
 */

/** @defgroup OV2640_Exported_Types
 * @{
 */

/**
 * @}
 */

/** @defgroup OV2640_Exported_Constants
 * @{
 */
/**
 * @brief  OV2640 ID
 */
#define OV2640_ID 0x26
#define OV2640_I2C_ADDRESS 0x60
/**
 * @brief  OV2640 Registers
 */

/* OV2640 Register Bank Select*/
#define OV2640_DSP_RA_DLMT 0xFF /* Select register bank */

/* Digital signal processor control register bank*/
#define OV2640_RDSP_RA_DLMT_SEL_DSP 0x00
#define OV2640_RDSP_RA_DLMT_SEL_SENSOR 0x01 /* Sensor control register bank */

/*
 * NOTE: all bits that not mentioned are considered as "reserved"
 **/

/* OV2640 Registers definition when DSP bank selected (0xFF = 0x00) */
#define OV2640_DSP_R_BYPASS 0x05 /* Bypass DSP */
#define OV2640_DSP_Qs 0x44       /* Quantization Scale Factor */
#define OV2640_DSP_CTRL 0x50     /* DSP Control register*/
#define OV2640_DSP_HSIZE1 0x51   /* H_SIZE (real/4) */
#define OV2640_DSP_VSIZE1 0x52   /* V_SIZE (real/4) */
#define OV2640_DSP_XOFFL 0x53    /* OFFXET_X */
#define OV2640_DSP_YOFFL 0x54    /* OFFSET_Y */
#define OV2640_DSP_VHYX 0x55     /* V_SIZE, H_SIZE, OFFSET_X/Y extension bit*/
#define OV2640_DSP_DPRP 0x56     /* */
#define OV2640_DSP_TEST 0x57     /* */
#define OV2640_DSP_ZMOW 0x5A     /* */
#define OV2640_DSP_ZMOH 0x5B     /* */
#define OV2640_DSP_ZMHH 0x5C     /* */
#define OV2640_DSP_BPADDR 0x7C   /* SDE Indirect Register Access: Address */
#define OV2640_DSP_BPDATA 0x7D   /* SDE Indirect Register Access: Data */

/* CTRL2 - Module Enable:
 * [5]-DCW
 * [4]-SDE
 * [3]-UV_ADJ
 * [2]-UV_AVG
 * [0]_CMX */
#define OV2640_DSP_CTRL2 0x86

/* CTRL3 - Module Enable
 * [7]-BPC
 * [6]-WPC */
#define OV2640_DSP_CTRL3 0x87
#define OV2640_DSP_SIZEL 0x8C  /* */
#define OV2640_DSP_HSIZE2 0xC0 /* */
#define OV2640_DSP_VSIZE2 0xC1 /* */

/* CTRL0-Module Enable
 * [7]-AEC_SEL
 * [6]-AEC_SEL
 * [5]-STAT_SEL-
 * [4]-VFIRST
 * [3]-YUV422
 * [2]-YUV_EN
 * [1]-RGB_EN
 * [0]-RAW_EN */
#define OV2640_DSP_CTRL0 0xC2

/* CTRL1-Module Enable
 * [7]-CIP
 * [6]-DMY
 * [5]-RWA_GMA
 * [4]-DG
 * [3]-AWB
 * [2]-AWB_GAIN
 * [1]-LENC
 * [0]-PRE */
#define OV2640_DSP_CTRL1 0xC3

/* R_DSP_SP
 * [7] Automode
 * [6:0] DVP Output Speed control
 * DVP PCLK =sysclk(48)/[6:0] (YUV0)
 * DVP PCLK =sysclk(48)/(2*[6:0]) (RAW) */
#define OV2640_DSP_R_DVP_SP 0xD3

/* IMAGE MODE
 * [6] Y8 enable for DVP
 * [4] JPEG compressed output enable
 * [3:2] DVP output format
 * 		 00-YUV422 01-RAW10 10-RGB565
 * [1] HREF timing select in DVP JPEG output mode
 *     0: HREF same as sensor
 *     1: HREF= VSYNC
 * [0] Byte swap enable*/
#define OV2640_DSP_IMAGE_MODE 0xDA

/* RESET
 * [6] Microcontroller
 * [5] SCCB
 * [4] JPEG
 * [2] DVP
 * [1] IPU
 * [0] CIF
 * */
#define OV2640_DSP_RESET 0xE0

/* SCCB master speed */
#define OV2640_DSP_MS_SP 0xF0

/* SCCB master ID */
#define OV2640_DSP_SS_ID 0xF7

/* SCCB slave control */
#define OV2640_DSP_SS_CTRL 0xF8

/* BIST */
#define OV2640_DSP_MC_BIST 0xF9

#define OV2640_DSP_MC_AL 0xFA    /* */
#define OV2640_DSP_MC_AH 0xFB    /* */
#define OV2640_DSP_MC_D 0xFC     /* SCCB protocol command register*/
#define OV2640_DSP_P_STATUS 0xFE /* SCCB protocol status register */

/* OV2640 Registers definition when sensor bank selected (0xFF = 0x01) */
/* AGC gain control LSBs
 * [7:0] gain setting (range 1x to 32x
 * gain = (bit[7]+1)*(bit[6]+1)*(bit[5]+1)*(bit[4]+1)*(bit[3:0]/16+1)*/
#define OV2640_SENSOR_GAIN 0x00

/*Common control
 * 0F - UXGA
 * 0A - SVGA
 * 06 - CIF
 * */
#define OV2640_SENSOR_COM1 0x03

/* Register 4
 * [7]  Horizontal mirror
 * [6]  Vertical flip
 * [4]  VREF[0]
 * [3]  HREF[0]
 * [1:0]  AEC[1:0]
 * */
#define OV2640_SENSOR_REG04 0x04

/* Register 8
 * Frame exposure One-pin Control Pre-charge Row number
 * */
#define OV2640_SENSOR_REG08 0x08

/* common control 2
 * [4]: Standby mode enable
 * [2]: Pin PWDN/RESETB used as SLVS/SLHS
 * [1:0]: Output drive select
 * 		  00: 1x capability
 * 		  01: 3x capability
 * 		  10: 2x capability
 * 		  11: 4x capability
 * */
#define OV2640_SENSOR_COM2 0x09

/* Product ID MSB */

#define OV2640_SENSOR_PIDH 0x0A

/* Product ID LSB */
#define OV2640_SENSOR_PIDL 0x0B

/* Common Control 3
 * [2] Set banding manually - 0:50Hz 1:60Hz
 * [1] Autoset banding
 * [0] Snapshot option - 1:Output single frame 0:live video after snapshot
 * */
#define OV2640_SENSOR_COM3 0x0C

/* Common Control 4
 * [2] clock output     0: tri-state data out uupon power-down
 * 	        	1: DAta output pin hold at last state
 * before power down
 * */
#define OV2640_SENSOR_COM4 0x0D

/* Auto Exposure Control 8bits for AEC[9:2] (AEC[15:10] in REG45, AEC[1:0] in
 * REG04) AEC[15:0]: exposure time T_ex = t_LINE * AEC[15:0]
 * */
#define OV2640_SENSOR_AEC 0x10

/* Clock rate control
 * [7] Internal frequancy doublers 1:ON/0:OFF
 * [5:0] clock divider
 *  */
#define OV2640_SENSOR_CLKRC 0x11

/* Common Control 7
 * [7] 1: Init system reset - factory reset
 * [6:4] Resolution
 * 					000: UXGA (full size)
 * 					001: CIF
 * 					100: SVGA
 * [2] Zoom mode
 * [1] Color bar test Pattern 0:OFF/1:ON
 * */
#define OV2640_SENSOR_COM7 0x12

/* Common Control 8
 * [5] Banding filter 0:OFF/1:ON
 * [2] AGC 0:manual/1:auto
 * [0] Exposure Control 0:manual/1:auto
 * */
#define OV2640_SENSOR_COM8 0x13

/* Common Control 9
 * [7:5] AGC gain ceiling GH[2:0]
 * 000:2x 001:4x 010:8x 011:16x 100:32x 101:64x 11x:128x
 * */
#define OV2640_SENSOR_COM9 0x14

/* Common Control 10 (only when DSP Bypass)
 * [7] pinoutput swap 0:CHSYNC 1:HREF
 * [6] pinoutput swap 1:CHSYNC 0:HREF
 * [5] PCLK 1:alway output
 *	        0: ouput qualified by HREF
 * [4] PCLK edge select 0: data update at PCLK rising edge
 *                      1: data update at PCLK falling edge
 * [3] HREF output polarity 0:positive
 *                          1:negative (negative for data valid)
 * [1] VSYNC polarity 0:positive/1:negative
 * [0] HSYNC polarity 0:positive/1:negative
 * */
#define OV2640_SENSOR_COM10 0x15

/* Horizontal Window start MSB 8bits (3 LSBs in REG32)
 * select start of Horizontal Window (each LSB represent 2 pixels)
 * */
#define OV2640_SENSOR_HREFST 0x17

/* Horizontal Window end MSB 8bits (3 LSBs in REG32)
 * select end of Horizontal Window (each LSB represent 2 pixels)
 * 75:UXGA 43:SVGA,CIF
 * */
#define OV2640_SENSOR_HREFEND 0x18

/* Vertical Window start MSB 8bits (3 LSBs in COM1)
 * select start of Horizontal Window (each LSB represent 2 scan lines)
 * */
#define OV2640_SENSOR_VSTART 0x19

/* Vertical Window end MSB 8bits (3 LSBs in COM1)
 * select end of Horizontal Window (each LSB represent 2 scan lines)
 * */
#define OV2640_SENSOR_VEND 0x1A

/* Manufactureer ID MSB */
#define OV2640_SENSOR_MIDH 0x1C
/* Manufactureer ID LSB */
#define OV2640_SENSOR_MIDL 0x1D

/* Luminance signal high range for AEC/AGC operation
 * AEC/AGC values will decrease in auto mode when average luminance > AEW[7:0]
 * */
#define OV2640_SENSOR_AEW 0x24
/* Luminance signal low range for AEC/AGC operation
 * AEC/AGC values will increase in auto mode when average luminance < AEW[7:0]
 * */
#define OV2640_SENSOR_AEB 0x25

/* Fast mode large step range threshold */
#define OV2640_SENSOR_W 0x26

/* Register 2A
 * [7:4] line inter val (LSBs in FRARL[7:0])
 * [3:2] HSYNC timing end point adjustment MSB 2 bits (LSBs in HEDY[7:0])
 * [1:0] HSYNC timing start point adjustment MSB 2 bits (LSBs in HEDY[7:0])
 *  */
#define OV2640_SENSOR_REG2A 0x2A

/*Framerat ~ line interval adjustment value - MSB in REG2A
 * ech LSB will add 1/1922 T_frame in UXGA and 1/1190 in SVGA to the frame
 * period
 * */
#define OV2640_SENSOR_FRARL 0x2B

/* VSYNC Pulse Width with LSB 8 bits, each LSB will add 1x t_line */
#define OV2640_SENSOR_ADDVSL 0x2D
/* VSYNC Pulse Width with MSB 8 bits, each MSB will add 256x t_line */
#define OV2640_SENSOR_ADDVHS 0x2E

/* Luminance average */
#define OV2640_SENSOR_YAVG 0x2F

/* HSYNC position and width, Start point in LSB 8bits
 * this and REF2A define HSYNC start postion, each LSB shift HSYNC start 2
 * pixels
 * */
#define OV2640_SENSOR_HSDY 0x30

/* HSYNC position and width, end point in LSB 8bits
 * this and REF2A define HSYNC end postion, each LSB shift HSYNC end 2 pixels
 * */
#define OV2640_SENSOR_HEDY 0x31

/* Register 32 - commen control 32
 * [7:6] pixel clock divide option
 *       00,01: no effect  10:devide by 2  11: divide by 4
 * [5:3] 3LSB of HREFEND[7:0]
 * [2:0] 3LSB of HREFST[7:0]
 *  */
#define OV2640_SENSOR_REG32 0x32

/* [2] zoom window horizontal start point*/
#define OV2640_SENSOR_ARCOM2 0x34

/* Register 45
 * [7:6] - AGC [9:8]
 * [5:0] - AEC [15:10]
 *  */
#define OV2640_SENSOR_REG45 0x45

/* Frame length adjustment LSB
 * each LSB add 1 horizontal lines
 * */
#define OV2640_SENSOR_FLL 0x46

/* Frame length adjustment MSB
 * each MSB add 256 horizontal lines
 * */
#define OV2640_SENSOR_FLH 0x47

/* Common control 19
 * [0:1] zoom mode vertival window start poin 2 LSBs
 * */
#define OV2640_SENSOR_COM19 0x48

/* [0:1] zoom mode vertival window start poin 8 MSBs*/
#define OV2640_SENSOR_ZOOMS 0x49

/* common control 22 - flash light control */
#define OV2640_SENSOR_COM22 0x4B

/* common sontrol 25
 * [7:6] 50Hz Banding AEC 8 LSBs
 * [5:4] 60Hz Banding AEC 8 LSBs
 * */
#define OV2640_SENSOR_COM25 0x4E

/* 50Hz Banding AEC 8 LSBs */
#define OV2640_SENSOR_BD50 0x4F

/* 60Hz Banding AEC 8 LSBs */
#define OV2640_SENSOR_BD60 0x50

/* Register 5D 5E 5F 60 - AVGsel[7:0][15:8][23:16][31:24] */
#define OV2640_SENSOR_REG5D 0x5D
#define OV2640_SENSOR_REG5E 0x5E
#define OV2640_SENSOR_REG5F 0x5F
#define OV2640_SENSOR_REG60 0x60

/* Histogram Algorithm Low Level */
#define OV2640_SENSOR_HISTO_LOW 0x61
/* Histogram Algorithm High Level */
#define OV2640_SENSOR_HISTO_HIGH 0x62

/**
 * @brief  OV2640 Features Parameters
 */
#define OV2640_BRIGHTNESS_LEVEL0 0x40 /* Brightness level -2         */
#define OV2640_BRIGHTNESS_LEVEL1 0x30 /* Brightness level -1         */
#define OV2640_BRIGHTNESS_LEVEL2 0x20 /* Brightness level 0          */
#define OV2640_BRIGHTNESS_LEVEL3 0x10 /* Brightness level +1         */
#define OV2640_BRIGHTNESS_LEVEL4 0x00 /* Brightness level +2         */

#define OV2640_BLACK_WHITE_BW 0x18          /* Black and white effect      */
#define OV2640_BLACK_WHITE_NEGATIVE 0x40    /* Negative effect             */
#define OV2640_BLACK_WHITE_BW_NEGATIVE 0x58 /* BW and Negative effect      */
#define OV2640_BLACK_WHITE_NORMAL 0x00      /* Normal effect               */

#define OV2640_CONTRAST_LEVEL0 0x3418 /* Contrast level -2           */
#define OV2640_CONTRAST_LEVEL1 0x2A1C /* Contrast level -2           */
#define OV2640_CONTRAST_LEVEL2 0x2020 /* Contrast level -2           */
#define OV2640_CONTRAST_LEVEL3 0x1624 /* Contrast level -2           */
#define OV2640_CONTRAST_LEVEL4 0x0C28 /* Contrast level -2           */

#define OV2640_COLOR_EFFECT_ANTIQUE 0xA640 /* Antique effect              */
#define OV2640_COLOR_EFFECT_BLUE 0x40A0    /* Blue effect                 */
#define OV2640_COLOR_EFFECT_GREEN 0x4040   /* Green effect                */
#define OV2640_COLOR_EFFECT_RED 0xC040     /* Red effect                  */
/**
 * @}
 */

/** @defgroup OV2640_Exported_Functions
 * @{
 */
void ov2640_Init(uint16_t DeviceAddr, uint32_t resolution);
void ov2640_Config(uint16_t DeviceAddr, uint32_t feature, uint32_t value,
                   uint32_t BR_value);
uint16_t ov2640_ReadID(uint16_t DeviceAddr);

void CAMERA_IO_Init(void);
void CAMERA_IO_Write(uint8_t addr, uint8_t reg, uint8_t value);
uint8_t CAMERA_IO_Read(uint8_t addr, uint8_t reg);
void CAMERA_Delay(uint32_t delay);

/* CAMERA driver structure */
extern CAMERA_DrvTypeDef ov2640_drv;
/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* __OV2640_H */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
