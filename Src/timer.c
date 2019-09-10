#include "timer.h"


void delayUS(uint16_t delay){
	__HAL_TIM_ENABLE(&htim2);
	uint16_t start = __HAL_TIM_GET_COUNTER(&htim2);

	while((__HAL_TIM_GET_COUNTER(&htim2) - start)<delay);
	__HAL_TIM_DISABLE(&htim2);
}

