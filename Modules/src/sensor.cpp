/**
 * @file BMI088Sensor.cpp
 * @brief Implementation of BMI088 accelerometer sensor wrapper class
 */

 #include "sensor.h"

 BMI088Sensor::BMI088Sensor() : initialized(false) 
 {
    device.accel_chip_id = 0x1E;
    device.gyro_chip_id = 0x0F;

 }
 
 bool BMI088Sensor::init(bmi08_intf interface_type) 
 {
     int8_t rslt;
     
     // Initialize interface (SPI or I2C)
     rslt = bmi08_interface_init(&device, interface_type);
     if (rslt != BMI08_OK) return false;
     
     // Initialize the sensor using bmi088_anymotion_init
     rslt = bmi088_anymotion_init(&device);
     if (rslt != BMI08_OK) return false;
     
     // Reset the accelerometer
     rslt = bmi08a_soft_reset(&device);
     if (rslt != BMI08_OK) return false;
     
     // Configure the accelerometer
     device.accel_cfg.power = BMI08_ACCEL_PM_ACTIVE;
     device.accel_cfg.odr = BMI08_ACCEL_ODR_100_HZ;
     device.accel_cfg.range = BMI088_ANYMOTION_ACCEL_RANGE_3G;
     device.accel_cfg.bw = BMI08_ACCEL_BW_NORMAL;
     
     // Set power mode
     rslt = bmi08a_set_power_mode(&device);
     if (rslt != BMI08_OK) return false;
     
     // Set measurement configuration
     rslt = bmi088_anymotion_set_meas_conf(&device);
     if (rslt != BMI08_OK) return false;
     
     initialized = true;
     return true;
 }
 
 bool BMI088Sensor::getData(struct bmi08_sensor_data* accel_data) 
 {
     if (!initialized) return false;
     
     int8_t rslt = bmi088_anymotion_get_data(accel_data, &device);
     return (rslt == BMI08_OK);
 }