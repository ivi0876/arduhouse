# ArduHouse

_This project simulates a home automation with functionalities to make it more functional_


### Pre requirements 📋

_Download librerias:_

- LiquidCrystal_I2C.h
- Servo.h

Software: IDE arduino

In here -> https://www.arduino.cc/en/software


### Instalación 🔧

_Inside the editor we go to program - Include library  - add zip_

## built with 🛠️

_tools used in this project_

* [Arduino Mega2560] - Control board
* [Servo] - garage engine
* [lcd] - data display screen
* [Ldr] - sensor control light
* [Tmp] - sensor control temperature


## Licencia 📄

licencia


## Next step

Apply API server with django or flask. connect with esp32

The house will be automated through several independent arduinos. Each arduino will connect to a centralized API to exchange different info.

Regarding the code, we'll divide each functional piece in different folders as:
LightSensor/
ParkingDoor/
TemperatureHumiditySensor/