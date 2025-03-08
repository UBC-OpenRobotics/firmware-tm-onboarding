#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "stm32h7xx_hal.h"
#include "stm32h723xx.h"

namespace UltrasonicSensor
{
    class Sensor {
    public:
        Sensor(GPIO_TypeDef* trigPort, uint16_t trigPin,
               GPIO_TypeDef* echoPort, uint16_t echoPin);

        uint16_t readPulse();
        float getDistanceCm();

    private:
        GPIO_TypeDef* trigPort;
        uint16_t trigPin;
        GPIO_TypeDef* echoPort;
        uint16_t echoPin;
        void delayMicroseconds(uint16_t us);
    };
}

#endif 
