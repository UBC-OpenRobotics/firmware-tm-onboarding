/**
 * @file BMI088Sensor.h
 * @brief Header file for BMI088 accelerometer sensor wrapper class
 */

 #ifndef BMI088_SENSOR_H
 #define BMI088_SENSOR_H
 
 #include "bmi088_anymotion.h"
 
 class BMI088Sensor {
 private:
     struct bmi08_dev device;
     bool initialized;
 
 public:
     /**
      * @brief Constructor for BMI088Sensor
      */
     BMI088Sensor();
 
     /**
      * @brief Initialize the BMI088 accelerometer sensor
      * 
      * @param interface_type Interface type (BMI08_SPI_INTF or BMI08_I2C_INTF)
      * @return true if initialization was successful, false otherwise
      */
     bool init(bmi08_intf interface_type = BMI08_SPI_INTF);
 
     /**
      * @brief Get accelerometer data from the sensor
      * 
      * @param accel_data Pointer to store the accelerometer data
      * @return true if data retrieval was successful, false otherwise
      */
     bool getData(struct bmi08_sensor_data* accel_data);
 };
 
 #endif // BMI088_SENSOR_H