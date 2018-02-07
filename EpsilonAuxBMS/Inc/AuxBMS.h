#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal_can.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_spi.h"

// Refer to https://docs.google.com/spreadsheets/d/1soVLjeD9Sl7z7Z6cYMyn1fmn-cG7tx_pfFDsvgkCqMU/edit?usp=sharing
#define AUX_READ_ORION_ENABLE_FREQ 1 // Every 1ms
#define AUX_SET_CONTACTOR_FREQ 20 // Every 20ms
#define AUX_UPDATE_AUX_VOLTAGE_FREQ 50 // Every 50ms

#define AUX_HEARBEAT_FREQ 1000 // 1Hz
#define AUX_HEARTBEAT_STDID 0x720U

#define AUX_STATUS_FREQ 100 // 10Hz
#define AUX_STATUS_STDID 0x721U

#define MAX_MIN_VOLTAGES_STDID 0x30A
// TODO
// Will implement when bill knows
#define MAX_VOLTAGE
#define MIN_VOLTAGE

#define CONTACTOR_WAIT_TIME 1000 // 1s
#define CURRENT_SENSE_RESISTOR 0.001 //1 mOhm
#define CURRENT_LOWER_THRESHOLD 0.3 // Lower current threshold
#define ADC_POLL_TIMEOUT 10

#define SPI_TIMEOUT 50
#define AUX_NOMINAL_VOLTAGE 12.0
#define AUX_ADC_NOMINAL_OUTPUT 0x2EB // Pattern = 2.63/3.6 * 0x3FF
// When ORION is coded, indices can be filled in


typedef struct AuxStatus
{
    unsigned int commonContactorState : 0;
    unsigned int chargeContactorState : 0;
    unsigned int dischargeContactorState : 0;
    uint16_t auxVoltage : 0x00;
    unsigned int strobeBmsLight : 0;
    unsigned int allowCharge : 0;
    unsigned int contactorError : 0;
} AuxStatus;

// Will include orion inputs once CAN details known

extern ADC_HandleTypeDef hadc1; // main.c
extern CAN_HandleTypeDef hcan1; // main.c
extern UART_HandleTypeDef huart3; // main.c
extern SPI_HandleTypeDef hspi3; // main.c

extern uint8_t orionOK; // Allows contactors to be turned on as long as the orion inputs are all good
extern uint8_t batteryVoltagesOK; // Allows contactors to be turned on as long as max/min voltages are all good
extern uint16_t orionBmsInputs[2];
extern AuxStatus auxStatus;


// Task for reading enables for charge, discharge, and safety, and max and min cell voltages from orion
// It will set an enable for setAuxContactorTask and can turn off all contactors,
// charge contactor if max cell voltage is too high, and discharge contactor is min cell voltage is too low
// whilst setAuxContactorTask is waiting
// arg: NULL
void readOrionInputTask(void const* arg)
// Task for turning on contactors
// arg: NULL
void setAuxContactorTask(void const* arg);
// Task for updating aux voltage
// arg: NULL
void updateAuxVoltageTask(void const* arg);
// Task for sending heartbeat via CAN
// arg: osMutexId* canHandleMutex
void sendHeartbeatTask(void const* arg);
// Task for sending aux status via CAN
// arg: osMutexId* canHandleMutex
void reportAuxToCanTask(void const* arg);
