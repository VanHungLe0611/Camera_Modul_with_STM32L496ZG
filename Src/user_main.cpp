#include "user_main.h"
#include "ov2640_dcmi_drv.h"
#include "dwt_stm32_delay.h"
#include "stm32l4xx_hal.h"

void user_code1() {
}

void user_code2() {

	// get instance of camera
	ov2640_dcmi_drv &cam_driver = ov2640_dcmi_drv::instance();
	// init camera
	Camera_StatusTypeDef cam_status = cam_driver.CAMERA_Init(IMAGE_RESOLUTION);
	// camera calibration lightroom delay time
	CAMERA_Delay_us(CAMERA_LIGHTROOM_CALIBRATION_DELAY);

	uint8_t count = 0;

	while (count < 5) {
		switch (cam_status) {
		case CAMERA_OK:
			cam_driver.CAMERA_Resume();
			cam_driver.CAMERA_SnapshotStart(CAMERA_BUFFER_INTERN);
			cam_driver.CAMERA_Stop();

			while (!uart_complete) {
			}
			uart_complete = 0;
			count++;

			break;
		case CAMERA_TIMEOUT:
			SEGGER_RTT_printf(0, "%s\n", "CAMERA_TIME_OUT");
			break;
		case CAMERA_ERROR:
			SEGGER_RTT_printf(0, "%s\n", "CAMERA_ERROR");
			break;
		}

	}
}

/* user code to test execution time of function */
void user_code3() {

	while (1) {

		/*Testing turn on and turn of  camera */

//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
//
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_RESET);

		/* Function is measured here */

		/* Testing Camera On Time*/
//		while (ov2640_ReadID(OV2640_I2C_ADDRESS) != OV2640_ID);
		/* Testing delay function of TIM, DWT and HAL_Delay*/
//		delayUS(1680);
//		HAL_Delay(1);
//		DWT_Delay_us(1680);

		/* Testing Camera Init Time*/
//		Camera_StatusTypeDef cam_status;
//		ov2640_dcmi_drv &cam_driver = ov2640_dcmi_drv::instance();
//		do {
//			cam_status = cam_driver.CAMERA_Init(IMAGE_RESOLUTION);
//		} while (cam_status != HAL_OK);

		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_SET);

	}
}

void loop() {
	HAL_Delay(1000);
}
