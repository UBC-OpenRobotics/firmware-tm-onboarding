#include "sensor.h"

namespace UltrasonicSensor
{
    Sensor::Sensor(GPIO_TypeDef* trigPort, uint16_t trigPin, GPIO_TypeDef* echoPort, uint16_t echoPin) {
        this->trigPort = trigPort;
        this->trigPin = trigPin;
        this->echoPort = echoPort;
        this->echoPin = echoPin;
    }

    // Send a trigger pulse to the sensor and measure duration of echo
    uint16_t Sensor::readPulse() {
        uint16_t pulse_duration = 0;
    
        // Ensure trigger pin is low
        HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_RESET);
        delayMicroseconds(2);  
    
        // Send 10 microsecond trigger pulse
        HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_SET);
        delayMicroseconds(10);  
        HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_RESET);
    
        // Wait for echo pin to go high
        while(HAL_GPIO_ReadPin(echoPort, echoPin) == GPIO_PIN_RESET);
    
        // Measure how long echo pin is high
        while(HAL_GPIO_ReadPin(echoPort, echoPin) == GPIO_PIN_SET) {
            pulse_duration++;
            delayMicroseconds(1);  // Increase count for each microsecond
        }
    
        return pulse_duration;
    }
    
    // Convert pulse duration into distance in cm
    float Sensor::getDistanceCm() {
        uint16_t pulse = readPulse();
        // The speed of sound is approximately 0.0343 cm per microsecond
        // Divide by 2 since the pulse makes a round trip
        return ((float)pulse * 0.0343f) / 2.0f;
    }

    void Sensor::delayMicroseconds(uint16_t us) {
        //Add this
    }
    
}
