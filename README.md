# Open Robotics Firmware Onboarding Project
## Sensor Library

### Overview:
This project focuses on developing a modular and reusable firmware library for the various sensors used in our robot. These modules will perform real-time data collection using an STM32 microcontroller and enable communication with the Software Team via ROS2 Humble.
To improve efficiency and responsiveness, we will incorporate Real-Time Operating System (RTOS) concepts, which will help with multitasking, task scheduling and interrupt management.

### Objectives:
- Program reusable sensor reading modules
- Interface with the STM32
- Use FreeRTOS to manage tasks and improve data collection efficiency
- Set up ROS2 Communication
  
### Sensor Table
| Sensor Type            | IMU     | Thermocouple  | Lidar     | Ultrasonic   | Hall-effect   | Encoder     |
|------------------------|---------|---------------|-----------|--------------|---------------|-------------|
| Functionality          |  Measures acceleration and angular velocity | Measures temperature by detecting changes in voltage | Utilizes laser pulses to measure distance from an object | Measures distance using sound waves to detect nearby objects | Detects the presence of magnetic fields to measure position or speed | Measures rotational or linear position by generating pulses as it moves|




