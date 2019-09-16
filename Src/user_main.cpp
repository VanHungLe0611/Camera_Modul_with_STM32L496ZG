#include "user_main.h"


void user_code1() {
}

void user_code2() {

	// get instance of camera
	OV2640 &cam_driver = OV2640::instance();
	// init camera
	Camera_StatusTypeDef cam_status = cam_driver.init(IMAGE_RESOLUTION);

	DCMI_Driver dcmi  ;
	dcmi.CAMERA_MsInit();

	// camera calibration lightroom delay time
	DWT_Delay_us(CAMERA_LIGHTROOM_CALIBRATION_DELAY);

	uint8_t count = 0;

	switch (cam_status) {
	case CAMERA_OK:
		dcmi.CAMERA_SnapshotStart(NUM_IMG,IMAGE_RESOLUTION);

		break;
	case CAMERA_TIMEOUT:
		SEGGER_RTT_printf(0, "%s\n", "CAMERA_TIME_OUT");
		break;
	case CAMERA_ERROR:
		SEGGER_RTT_printf(0, "%s\n", "CAMERA_ERROR");
		break;
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
