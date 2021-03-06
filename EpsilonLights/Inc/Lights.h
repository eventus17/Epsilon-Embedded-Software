#pragma once

#include <stdbool.h>

#include "stm32f4xx.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_can.h"

// Refer to https://docs.google.com/spreadsheets/d/1soVLjeD9Sl7z7Z6cYMyn1fmn-cG7tx_pfFDsvgkCqMU/edit?usp=sharing
#define LIGHTS_UPDATE_FREQ 10 // Every 10ms
#define LIGHT_OFF 1 // Active low
#define LIGHT_ON 0
#define BLINKER_FREQ 1000 // 1Hz

#define LIGHTS_HEARTBEAT_FREQ 1000 // 1Hz = 1000ms
#define LIGHTS_HEARTBEAT_STDID 0x710U

#define LIGHTS_STATUS_FREQ 200 // 5Hz = 200ms
#define LIGHTS_STATUS_STDID 0x711U

#define LIGHTS_INPUT_STDID 0x701U
#define HOFF_INPUT_INDEX 0
#define HLOW_INPUT_INDEX 1
#define HHIGH_INPUT_INDEX 2
#define RSIGNAL_INPUT_INDEX 3
#define LSIGNAL_INPUT_INDEX 4
#define HAZARDS_INPUT_INDEX 5

#define DRIVERS_INPUTS_STDID 0x703U
#define BRAKES_INPUT_INDEX_P1 3 // 24 = [*3*] >> 0
#define BRAKES_INPUT_INDEX_P2 0 // 24 = [3] >> *0*

#define BATTERY_STAT_ERRORS_STDID 0x303U
// Mask for to check faults defined for Tritium BMS in TRI67.010 ver 2
// Check for "cell over voltage" 0x01, "cell under voltage" 0x02, and "cell over temperature" 0x04
#define BATTERY_CRIT_FAULT_MASK 0x07

typedef struct LightsStatus
{
    unsigned int lowBeams : 1;
    unsigned int highBeams : 1;
    unsigned int brakes : 1;
    unsigned int leftSignal : 1;
    unsigned int rightSignal : 1;
    unsigned int bmsStrobeLight : 1;
} LightsStatus;

typedef struct SigLightsHandle
{
    uint8_t left;
    uint8_t right;
} SigLightsHandle;

extern CAN_HandleTypeDef hcan2; // main.c
extern uint8_t lightsInputs;
extern uint8_t batteryErrors[5];
extern uint8_t driversInputs[4];
extern SigLightsHandle sigLightsHandle;

// Task for updating GPIOs
// arg : NULL
void updateLightsTask(void const* arg);
// Blink signal lights based on SigLightsHandle global struct
// Handle actual on/off of blinker lights
// arg : NULL
void blinkSignalLightsTask(void const* arg);
// Task for sending lights statuses via CAN
// arg : osMutexId* canHandleMutex
void reportLightsToCanTask(void const* arg);
// Task for sending heartbeat via CAN
// arg : osMutexId* canHandleMutex
void sendHeartbeatTask(void const* arg);
