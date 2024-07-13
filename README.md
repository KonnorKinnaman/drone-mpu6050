# Gyroscopically Actuated Drone Project
This repository encompasses all of the modules I used to create my gyroscopically actuated drone.
Most of the files in this repository are meant to be used in Atmel Studio. Also included are .ino files
used to test the hardware in the Arduino IDE.


## Hardware
### On the Glove
* Atmega328p on Pro Mini Board
    * CP2102 USB - TTL Converter for Flashing Microcontroller
* MPU6050 Module -  for Accelerometer and Gyroscope
* Analog Joystick - for controlling propellor speed
* Adafruit MPM3610 Buck Converter - Converts 9V from battery to 5V for all modules
* Adafruit 8 Channel Bidirectional Level Shifter - Converts 5V logic to 3.3V logic for SPI transceiver
* nRF24L01+ Transmitter
* 9V Battery

### On the Drone
* Betaflight OMNIBUSF4SD with STM32F405
* Mateksys Power Distribution Board
* nRF24L01+ Transmitter
   * Atmega328p as translater for OMNIBUS
* BLHELI 20A ESC's (x4)
* 2204-2300KV Brushless Motors (x4)
* 5045R Propellers
* 3S LiPo Battery

## Notes About Repo
All Datasheets for hardware are included for reference, as well as all other reference material
used in determining how to select/link hardware.

Avrdude application and CONF file included for help with structuring
argument and command for flashing the 328p.

manualControl project files includes modules for UART. These modules were only meant to be used during
testing and development, and will not be used in the final product.

Betaflight Configurator was used for flashing the flight controller, but not included in the repo

Images of the finished project will be put in the images folder when all parts are finished and solidified.
