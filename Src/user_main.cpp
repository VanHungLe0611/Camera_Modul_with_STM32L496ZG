#include "user_main.h"
#include "dcmi_driver.h"
void user_code1() {}

void user_code2() {
  // init camera
  //  BSP_CAMERA_Init(IMAGE_RESOLUTION);
  DCMI_Driver &cam_driver = DCMI_Driver::instance();
  cam_driver.CAMERA_Init(IMAGE_RESOLUTION);

  //  BSP_CAMERA_SnapshotStart(image_data);
  cam_driver.CAMERA_SnapshotStart(image_data);
}

void user_code3() {}

void loop() { HAL_Delay(1000); }
