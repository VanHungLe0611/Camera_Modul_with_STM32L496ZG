#include "user_main.h"
#include "ov2640_dcmi_drv.h"
void user_code1() {}

void user_code2() {
  // init camera
  //  BSP_CAMERA_Init(IMAGE_RESOLUTION);
  ov2640_dcmi_drv &cam_driver = ov2640_dcmi_drv::instance();
  cam_driver.CAMERA_Init(IMAGE_RESOLUTION);

  //  BSP_CAMERA_SnapshotStart(image_data);
  cam_driver.CAMERA_SnapshotStart(CAMERA_BUFFER);
}

void user_code3() {}

void loop() { HAL_Delay(1000); }
