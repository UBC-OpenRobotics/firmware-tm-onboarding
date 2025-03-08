#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern UART_HandleTypeDef huart1; // Use the correct UART instance

void sensor_init(void) {
    printf("TF-LIDAR Mini Initialized.\n");
}

int sensor_read(TFminiData *data) {
    uint8_t buffer[TFMINI_FRAME_SIZE];

    // Read data using STM32 HAL
    if (HAL_UART_Receive(&huart1, buffer, TFMINI_FRAME_SIZE, 100) != HAL_OK) {
        return -1; // Error reading data
    }

    // Validate frame header
    if (buffer[0] != TFMINI_FRAME_HEADER || buffer[1] != TFMINI_FRAME_HEADER) {
        return -2; // Invalid frame
    }

    // Extract data
    data->distance = buffer[2] | (buffer[3] << 8);
    data->strength = buffer[4] | (buffer[5] << 8);

    return 0; // Success
}
