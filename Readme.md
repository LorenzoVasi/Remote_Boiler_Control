# Mountain House Boiler Control With SIM

This project is used to control the boiler of the mountain house using a sim (being absent of wired connection)

## Components

- [x] Arduino UNO

- [x] DHT22

- [x] Relay5V Module

- [x] GPRS SIM800 Module 

- [x] Button

- [x] Led Status RED

- [ ] 3D Printed Case (take measure of sensors [when arrived])

- [x] 12V PowerSupply

- [x] StepDown for High Alimentation

- [x] Mammut

- [x] Cables

- [x] Sim ThingsMobile

## Requests

### Client Application (ANDROID)

Through this app it is possible to manage the structure of the message to be sent to arduino for boiler management (works in progress)

## Arduino Software

Adjust the temperature with SMS as Input and turn off when [OR]:

1. Receive an SMS with OFF

2. Receive an SMS with DATE of TURNOFF

3. Click Button for TurnOFF 
