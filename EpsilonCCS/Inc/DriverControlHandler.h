#pragma once

#include "stm32f4xx.h"
//#include "stm32f4xx_hal_conf.h"
//#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_can.h"

extern CAN_HandleTypeDef hcan2; // main.c
extern osMessageQId canQueue;
extern osPoolId canPool;

void handleDriverMsgTask(void const* arg);
