##AVR-Battery-Monitor
A simple library for small projects utilizing the internal ADC reference of the arduino nano, uno, and micro. Uses only an external capacitor and 2 resistors to monitor a lithium ion battery for over voltage and under voltage.

##How to Use
Following this example schematic use a capacitor of any value and connect it across AREF and GND then add a voltage divder such that (R1)/(R1 + R2) < 0.2 
![yspyG](https://raw.github.com/yspyG/AVR-Battery-Monitor/etc/schematic.png "yspyG")

This library configures the ADC to use the internal 1.1v reference so be aware that any ADC readings you take after initializing this library will be on a scale from 0-1.1V rather than the standard 0-5V. Also this library does not support over-current protection currently, consider adding a polyfuse or other current limiting device to a project using this library. 