# AVR-Battery-Monitor
A simple and straight-forward library for monitoring batteries powering an Arduino or AVR board using the ATmega328 (support for other micro-controllers is in the works). Uses the absolute minimum of external components, requiring only a current shunt to monitor current use. 

## How to Use


![yspyG](https://github.com/yspyG/AVR-Battery-Monitor/blob/master/etc/schematic.png?raw=true "yspyG")

This library utilizes the AVR's internal 1.1V bandgap reference to determine the actual voltage at its pins, it requires only a the connections shown in the schematic above. The shunt reistor is technically optional if you don't need the current measurements. For more information about how the library works check out the hackaday.io page here: https://hackaday.io/project/167181-lithium-ion-battery-monitor-library-for-arduino

Any value of shunt resistor can be used, for reading smaller currents larger shunt resistors should be used. A resistor value of .05 ohms will give a resolution of about 100mA. 
## Included functions

Currently supported functions for this library include: 

### Constructors 

`BatteryMonitor(int batteryPin)` - Initializing only the battery monitor pin connected to the positive terminal of the battery. 
`BatteryMonitor(int batteryPin, int currentSensePin)` - Initializing the battery monitor pin and the currentSensePin (both of these should read as close to the shunt resistor as possible)

### Functions

`void setCurrentSensePin(int currentSensePin)` - sets the current sense pin
`void setCurrentSenseResistance(float r)` - sets the shunt resistor value, use whatever works for you. 
`float getCurrentBatteryVoltage()` - returns the current battery voltage as a floating point value.
`float getCurrentOperatingVoltage()` - returns the current voltage the micro-controller is operating at (intended for circuits powered by boost-converters, currently has limited testing)
`float getBatteryCurrent()` - returns the amount of current (in amps) being drawn from the battery (waiting on parts to test this thoroughly) 