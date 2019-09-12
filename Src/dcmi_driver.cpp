#include "dcmi_driver.h"
#include "stm32l4xx_hal.h"

// TODO: do we need this?
/**
 * @brief  Initializes the camera hardware
 */

#define IMG_SIZE_TEMP 160*120*2
#define NUM_IMG 8

uint8_t imgBuff[IMG_SIZE_TEMP * NUM_IMG];

uint8_t captureCmplt = 0;
uint8_t uartCmplt = 0;

void DCMI_Driver::CAMERA_MsInit(void) {
	HAL_DCMI_MspInit(&hdcmi);
}

// TODO: test video capture (dcmi continuous)
/*
 * @brief  Starts the camera capture in continuous mode.
 * @param  buff: pointer to the camera output buffer
 */
void DCMI_Driver::CAMERA_ContinuousStart(uint8_t *buff) {
	/* Start the camera capture */
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t) buff,
			GetSize(current_resolution));
}

/**
 * @brief  Starts the camera capture in snapshot mode.
 * @param  buff: pointer to the camera output buffer
 */
void DCMI_Driver::CAMERA_SnapshotStart(uint8_t *buff) {

	/* Start the camera capture */

	uint8_t *tempAddr;
	uint8_t count = 0;
	HAL_StatusTypeDef res;

	while (count < NUM_IMG) {

		CAMERA_Resume();

		__HAL_DCMI_ENABLE_IT(&hdcmi,
				DCMI_IT_FRAME | DCMI_IT_LINE | DCMI_IT_VSYNC);

		res = HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT,
				(uint32_t) &imgBuff[count * IMG_SIZE_TEMP],
				GetSize(current_resolution));

		while (!captureCmplt) {
		}

		CAMERA_Stop();
		count++;
		captureCmplt = 0;

	}

	count = 0;

	while (count < NUM_IMG) {
		// transfer data from sram to host
		res = HAL_UART_Transmit_DMA(&huart5,  &imgBuff[count * IMG_SIZE_TEMP],
		IMAGE_MEMSIZE_IN_BYTE);
		while (!uartCmplt) {
		}
		count++;
		uartCmplt = 0;
	}
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
	}
		break;
	case CAMERA_R320x240: {
		size = 0x9600;
	}
		break;
	case CAMERA_R480x272: {
		size = 0xFF00;
	}
		break;
	case CAMERA_R640x480: {
		size = 0x25800;
	}
		break;
	default: {
		break;
	}
	}

	return size;
}

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
	SEGGER_RTT_printf(CAMERA_COMMON_DEBUG_RTT_DISABLE,
			"--Total line read: %d\n", lineNum);
#endif
	lineNum = 0;
}

void DCMI_Driver::CAMERA_FrameEventCallback(void) {

	__HAL_DCMI_CLEAR_FLAG(&hdcmi, DCMI_IT_FRAME);

	captureCmplt = 1;
}

void DCMI_Driver::CAMERA_ErrorCallback(void) {
#ifdef CAMERA_DEBUG_RTT
	SEGGER_RTT_printf(CAMERA_EVENT_DEBUG_RTT_DISABLE,
			"ERROR: Frame synchonization error event\n");
#endif
}

/**
 * @brief  Handles DCMI interrupt request.
 */
void DCMI_Driver::CAMERA_IRQHandler(void) {
	HAL_DCMI_IRQHandler(&hdcmi);
}

/**
 * @brief  Handles DMA interrupt request.
 */
void DCMI_Driver::CAMERA_DMA_IRQHandler(void) {
	HAL_DMA_IRQHandler(hdcmi.DMA_Handle);
}

/*
 *--------------------- HAL IRQ overloadedfunctions-----------------------
 * These functions must be here, so that dcmi events can be called
 */
/**
 * @brief  Line event callback
 * @param  hdcmi: pointer to the DCMI handle
 */
void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi) {
	DCMI_Driver::CAMERA_LineEventCallback();
}

/**
 * @brief  VSYNC event callback
 * @param  hdcmi: pointer to the DCMI handle
 */
void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi) {
	DCMI_Driver::CAMERA_VsyncEventCallback();
}

/**
 * @brief  Frame event callback
 * @param  hdcmi: pointer to the DCMI handle
 */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) {
	DCMI_Driver::CAMERA_FrameEventCallback();
}

/**
 * @brief  Error callback
 * @param  hdcmi: pointer to the DCMI handle
 */
void HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi) {
	DCMI_Driver::CAMERA_ErrorCallback();
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	uartCmplt = 1;
}

