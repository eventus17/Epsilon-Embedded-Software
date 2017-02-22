#pragma once

#include "stm32f4xx.h"
//#include "stm32f4xx_hal_conf.h"
//#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_can.h"

#define LIGHTS_CAN_FREQ 100
#define LIGHTS_STDID 0x701U
#define LIGHTS_DLC 1

#define MUSIC_CAN_FREQ 200
#define MUSIC_STDID 0x702U
#define MUSIC_DLC 1

#define DRIVER_CAN_FREQ 50
#define DRIVER_STDID 0x703U
#define DRIVER_DLC 4

extern CAN_HandleTypeDef hcan2; // main.c
extern osMessageQId canQueue;
extern osPoolId canPool;

void handleDriverMsgTask(void const* arg);
