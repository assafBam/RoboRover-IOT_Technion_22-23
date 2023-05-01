# RoboRover-IOT_Technion_22-23

## Team members:
* Assaf Bamberger
* Itay Stolear
* Sally Turutov

## Project Description:
The purpose of this project is to demonstrate control of a simple robot throw a WEB interface from the internet (from all over the world)

this Git contains the following directories:
1. **robot-esp32:** the code for the ESP32-CAM micro-controller that runs the robot
2. **Unit tests:** basic tests for the ESP- blink, motor driver
3. **robot-Rpi:** the python code for the respbarryPi

furthermore, this Git includes
* **Schematic_roborover:** the connection diegram for the robot
* **TB6612FNG_Library:** a library for controling the motors with the motor drivers

## Our poster:
<img width="237" alt="image" src="https://user-images.githubusercontent.com/50671687/216149672-b6aa63fd-a5e4-4496-a6e0-24f905f1e953.png">

##ESP32 libraries:
* ESP32Servo
* WiFi
* BluetoothSerial
* HardwareSerial
* esp_http_server
* esp_timer
* esp_camera
* img_converters

##Python libreries on the respbarryPi:
* wifi
* os
* bluedot
* qrcode
* pyngrok
