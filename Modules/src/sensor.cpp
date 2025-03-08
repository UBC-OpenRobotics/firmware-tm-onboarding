#include "sensor.h"
#include <stdio.h>
#include <string.h>

// Initialize the hall-effect sensor
HAL_StatusTypeDef HallSensor_Init(HallSensor_Config_t* config) {
    if (config == NULL) {
        return HAL_ERROR;
    }

    // For digital sensors, configure GPIO as input
    if (!config->is_analog) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        
        // Configure GPIO pin
        GPIO_InitStruct.Pin = config->pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(config->port, &GPIO_InitStruct);
    }
    // For analog sensors, ADC should already be initialized
    else {
        if (config->hadc == NULL) {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}

// Read the hall-effect sensor value
HAL_StatusTypeDef HallSensor_Read(HallSensor_Config_t* config, uint32_t* value) {
    if (config == NULL || value == NULL) {
        return HAL_ERROR;
    }

    // For digital sensors, read GPIO pin
    if (!config->is_analog) {
        *value = HAL_GPIO_ReadPin(config->port, config->pin);
        return HAL_OK;
    }
    // For analog sensors, read ADC value
    else {
        if (config->hadc == NULL) {
            return HAL_ERROR;
        }

        // Configure ADC channel
        ADC_ChannelConfTypeDef sConfig = {0};
        sConfig.Channel = config->adc_channel;
        sConfig.Rank = ADC_REGULAR_RANK_1;
        sConfig.SamplingTime = ADC_SAMPLETIME_64CYCLES_5;
        sConfig.SingleDiff = ADC_SINGLE_ENDED;
        sConfig.OffsetNumber = ADC_OFFSET_NONE;
        sConfig.Offset = 0;
        if (HAL_ADC_ConfigChannel(config->hadc, &sConfig) != HAL_OK) {
            return HAL_ERROR;
        }

        // Start ADC conversion
        if (HAL_ADC_Start(config->hadc) != HAL_OK) {
            return HAL_ERROR;
        }

        // Wait for conversion to complete
        if (HAL_ADC_PollForConversion(config->hadc, 100) != HAL_OK) {
            return HAL_ERROR;
        }

        // Read ADC value
        *value = HAL_ADC_GetValue(config->hadc);

        // Stop ADC conversion
        if (HAL_ADC_Stop(config->hadc) != HAL_OK) {
            return HAL_ERROR;
        }

        return HAL_OK;
    }
}

// Print the hall-effect sensor value to the console
HAL_StatusTypeDef HallSensor_PrintValue(HallSensor_Config_t* config, UART_HandleTypeDef* huart) {
    if (config == NULL || huart == NULL) {
        return HAL_ERROR;
    }

    uint32_t value;
    HAL_StatusTypeDef status = HallSensor_Read(config, &value);
    
    if (status != HAL_OK) {
        return status;
    }

    char buffer[100];
    int len;

    if (!config->is_analog) {
        // For digital sensors, print 0 or 1
        len = sprintf(buffer, "Hall Sensor [%s]: %s\r\n", 
                     config->name, 
                     (value == 0) ? "No magnetic field detected" : "Magnetic field detected");
    } else {
        // For analog sensors, print raw value and interpreted strength
        len = sprintf(buffer, "Hall Sensor [%s]: Raw value: %lu, Magnetic field strength: ", 
                     config->name, value);
        
        // Simple interpretation of magnetic field strength
        if (value < 1000) {
            strcat(buffer, "Weak\r\n");
        } else if (value < 3000) {
            strcat(buffer, "Medium\r\n");
        } else {
            strcat(buffer, "Strong\r\n");
        }
        
        len = strlen(buffer);
    }

    // Transmit data via UART
    if (HAL_UART_Transmit(huart, (uint8_t*)buffer, len, 1000) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}
