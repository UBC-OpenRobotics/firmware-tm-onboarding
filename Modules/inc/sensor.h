#ifndef SENSOR_H
#define SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"
#include "stm32h723xx.h"
#include <stdint.h> 

// Hall-effect sensor structure
typedef struct {
    GPIO_TypeDef* port;     // GPIO port for the sensor input
    uint16_t pin;           // GPIO pin for the sensor input

    ADC_HandleTypeDef* hadc; // ADC handle for analog sensors (NULL for digital)
    uint32_t adc_channel;   // ADC channel (only used if hadc is not NULL)

    uint8_t is_analog;      // Flag to indicate if sensor is analog (1) or digital (0)

    char name[32];          // Sensor name for display purposes
} HallSensor_Config_t;

// Initalize hall-effect sensor
HAL_StatusTypeDef HallSensor_Init(HallSensor_Config_t* config);

// Read hall eff-effect sensor value 
HAL_StatusTypeDef HallSensor_Read(HallSensor_Config_t* config, uint32_t* value);

// Print hte hall-effect sensor value to console
HAL_StatusTypeDef HallSensor_PrintValue(HallSensor_Config_t* config, UART_HandleTypeDef* huart);

#ifdef __cplusplus
}
#endif

#endif
