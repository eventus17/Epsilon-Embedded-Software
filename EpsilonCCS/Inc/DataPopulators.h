#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_hal_can.h"

#include "BatteryData.h"
#include "BatteryFaultsData.h"
#include "DriverControlData.h"
#include "KeyMotorData.h"
#include "LightsData.h"
#include "MotorDetailsData.h"
#include "MotorFaultsData.h"
#include "MpptData.h"

extern struct BatteryData batteryData;
extern struct BatteryFaultsData batteryFaultsData;
extern struct DriverControlData driverControlData;
extern struct KeyMotorData keyMotorData;
extern struct LightsData lightsData;
extern struct MotorDetailsData motor0DetailsData;
extern struct MotorDetailsData motor1DetailsData;
extern struct MotorFaultsData motorFaultsData;
extern struct MpptData mpptData[];

void populateBatteryData(uint8_t data[8]);
void populateBatteryFaultsData(uint8_t data[8]);
void populateDriverControlData(uint8_t data[8]);
void populateKeyMotorData(uint8_t data[8]);
void populateLightsData(uint8_t data[8]);
void populateMotorDetailsData(uint8_t data[8]);
void populateMotorFaultsData(uint8_t data[8]);
void populateMpptData(uint8_t data[8]);
