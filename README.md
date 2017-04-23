AHABus - Arduino Payload Bus
============================

    Version 0.1-A3
    Author: Amy parent <amy@amyparent.com>
    Date:   2017-04-21
    

This is a one-file library for the Arduino IDE, that provides an API to write
AHABus payloads using Arduino-compatible boards. Installation only requires 
ahabus.ino to be added to an Arduino project. `BusInit()` should be called
in `setup()`. Bus write routines return true if data was written successfully,
false otherwise.
