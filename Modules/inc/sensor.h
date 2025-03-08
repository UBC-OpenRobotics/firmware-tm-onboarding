#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include "usart.h"

#define TFMINI_FRAME_HEADER 0x59
#define TFMINI_FRAME_SIZE 9

typedef struct {
    uint16_t distance;
    uint16_t strength;
} TFminiData;

void sensor_init(void);
int sensor_read(TFminiData *data);

#endif // SENSOR_H
