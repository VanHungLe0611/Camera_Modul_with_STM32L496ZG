#ifndef INC_VAR_INTERFACE_H_
#define INC_VAR_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Image mem size in bytes */
#define CAMERA_R160x120_COLOR_MEMSIZE 0x9600
#define CAMERA_R320x240_COLOR_MEMSIZE 0x25800
#define CAMERA_R480x272_COLOR_MEMSIZE 0x3FC00
#define CAMERA_R640x480_COLOR_MEMSIZE 0x96000
#define CAMERA_R160x120_MONOC_MEMSIZE 0x4B00
#define CAMERA_R320x240_MONOC_MEMSIZE 0x12C00
#define CAMERA_R480x272_MONOC_MEMSIZE 0x1FE00
#define CAMERA_R640x480_MONOC_MEMSIZE 0x4B000

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_dcmi;
extern DCMI_HandleTypeDef hdcmi;
extern UART_HandleTypeDef huart4;

extern uint8_t image_data[];
static uint32_t lineNum;

/* CAMERA GLOBAL SETTING */
#define CAMERA_DELAY_INTERVAL 500  // ms
#define IMAGE_RESOLUTION CAMERA_R160x120
#define IMAGE_SIZE CAMERA_R160x120_COLOR_MEMSIZE
#define IMAGE_BANDFILTER_ENABLE 1

/*RTT debug activation*/
#define CAMERA_DEBUG_RTT_DISABLE 0

#ifdef __cplusplus
}
#endif

#endif /* INC_VAR_INTERFACE_H_ */
