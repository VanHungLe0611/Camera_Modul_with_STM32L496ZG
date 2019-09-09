#include "user_main.h"
#include "ov2640_dcmi_drv.h"

void user_code1() {
}

void user_code2() {

	//  BSP_CAMERA_Init(IMAGE_RESOLUTION)
	// init camera
	ov2640_dcmi_drv &cam_driver = ov2640_dcmi_drv::instance();
	int i = 0;

	/* GPIOC & PIN 2 to measure execution time of CAMERA_Init function*/
	//	GPIOC->BSRR |= GPIO_BSRR_BS_2; // GPIO_OUT_PUT = HIGH

	Camera_StatusTypeDef cam_status = cam_driver.CAMERA_Init(IMAGE_RESOLUTION);
	//	GPIOC->BSRR |= GPIO_BSRR_BR_2; // GPIO_OUT_PUT = LOW

    while(i < 5)
	switch (cam_status) {
	case CAMERA_OK:
		//  BSP_CAMERA_SnapshotStart(image_data);
		cam_driver.CAMERA_Resume();
		cam_driver.CAMERA_SnapshotStart(CAMERA_BUFFER_INTERN);
		cam_driver.CAMERA_Stop();

		while(!uart_complete){}
		uart_complete = 0;
		i++;

		break;
	case CAMERA_TIMEOUT:
		SEGGER_RTT_printf(0, "%s\n", "CAMERA_TIME_OUT");
		break;
	case CAMERA_ERROR:
		SEGGER_RTT_printf(0, "%s\n", "CAMERA_ERROR");
		break;
	}

}


// user code, which is used for Testing
void user_code3() {

	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_RESET);


	/* Function is measured here */
	while(ov2640_ReadID(OV2640_I2C_ADDRESS) != OV2640_ID){
		SEGGER_RTT_printf(0,"%s \n", "Camera was not connected");
	}

	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_SET);
}

void loop() {
	HAL_Delay(1000);
}
