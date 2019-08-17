# AVR-Battery-Monitor
A simple library for small projects utilizing the internal ADC reference of the arduino nano, uno, and micro. Uses only an external capacitor and 2 resistors to monitor a lithium ion battery for over voltage and under voltage.

## How to Use
Following this example schematic use a capacitor of any value and connect it across AREF and GND then add a voltage divder such that (R2)/(R1 + R2) < 0.2 
![yspyG](https://github.com/yspyG/AVR-Battery-Monitor/blob/master/etc/schematic.png?raw=true "yspyG")

This library configures the ADC to use the internal 1.1v reference so be aware that any ADC readings you take after initializing this library will be on a scale from 0-1.1V rather than the standard 0-5V. Also this library does not support over-current protection currently, consider adding a polyfuse or other current limiting device to a project using this library. 

## Included functions

`checkBattery()` automatically checks battery voltage and carries out default actions depending on the battery voltage. 
* battery high (overvoltage) causes both the lowVoltage and batteryGood indicators pins to go HIGH
* voltage between highVoltage and lowVoltage causes the batteryGood indicator pin to go HIGH
* voltage between lowVoltage and criticalVoltage causes the lowVoltage indicator pin to go HIGH
* voltage below the criticalVoltage causes the arduino to enter deepSleep and turn all output pins low. 

alternatively the battery can be monitored using the included functions `isGood()`, `isHigh()`, `isLow()`, `isCritical()`. 
* `isHigh()` returns true if battery voltage > highVoltage
* `isGood()` returns true if battery voltage > lowVoltage && < highVoltage 
* `isLow()` returns true if battery voltage > criticalVoltage && < lowVoltage
* `isCritical()` returns true if battery voltage < criticalVoltage

using these you can configure your own actions at various battery states. If that's not enough control for you then you can also use the function `getCurrentBatteryVoltage()` which will return the current battery voltage as a float. 

Additionally the library allows you to configure your own voltage ranges, resistors, and action pin:
* `setGoodNotificationPin(int pin)` sets the pin to be turned HIGH if the battery voltage is in its ideal range
* `setLowNotificationPin(int pin)` sets the pin to be turned HIGH if the battery voltage is in the low range but above critical
* `setLowVoltage(float voltage)` sets the low voltage value (default value is 3.2V)
* `setHighVoltage(float voltage)` sets the high voltage (overvoltage) value (default value is 4.3V)
* `setCriticalVoltage(float voltage)` sets the critical voltage level (default value is 2.8V)
* `setR1(long value)` sets the value of R1 to value (in ohms so 10k = 10000)
* `setR2(long value)` sets the value of R2 to value (same as above)
