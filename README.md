LedControl
==========
LedControl is an [Arduino](http://arduino.cc) library for MAX7219 and MAX7221 Led display drivers.
The code also works with the [Teensy (3.1)](https://www.pjrc.com/teensy/)

Hardware SPI modifications  by Jack Zimmermann for supporting hardware SPI using the predefined MOSI and SCK pins on supported devices.

Library version which supports both software and hardware SPI created by Stephen Gordon.

Usage
-----
Declare a variable of type LedControl_HW_SPI or LedControl_SW_SPI and use the relevant constructor. Then use the normal LedControl API - begin(), setRow(), setCol, setLed(), etc..

For software SPI, you can use whatever pins you like. The overall transfer speed is slower, and you cannot limit the SPI communication speed. This can be a problem in applications where interference is an issue.

For hardware SPI, you need to use the assigned hardware SPI pins, but the speed is 20x or greater and you can set a limit on the speed. The table below for correct pins for some devices. Some Arduinos doesn't have the SCK pin so this library won't work on those. The Chip Select(csPin) can be any pin but be careful to avoid pins that are used for SD transfers, on-board memory and other things - check your board documentation. The new initialisation only needs the csPin and number of devices.

HW SPI Pin Assignments
----------------------

| Arduino Board | MOSI | MISO | SCK | SS (Slave) | SS (Master) |
|---------------|------|------|-----|------------|-------------|
| Uno or Duemilanove | 11 or ICSP-4 | 12 or ICSP-1 | 13 or ICSP-3 | 10 | - |
| Mega1280 or Mega2560 | 51 or ICSP-4 | 50 or ICSP-1 | 52 or ICSP-3 | 53 | - |
| Leonardo | ICSP-4 | ICSP-1 | ICSP-3 | - | - |
| Due | ICSP-4 | ICSP-1 | ICSP-3 | - | 4, 10, 52 |
| Deek-Robot Arduino | 11 | 12 | 13 | - | 10 |	


Documentation
-------------
Documentation for the LedControl API  is on the [Github Project Pages](http://wayoda.github.io/LedControl/)

Download
--------
The latest binary version of the original Library is always available from the 
[LedControl Release Page](https://github.com/wayoda/LedControl/releases) 


Install
-------
The library can be installed using the [standard Arduino library install procedure](http://arduino.cc/en/Guide/Libraries)  







