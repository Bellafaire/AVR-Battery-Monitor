/*
(c) Copyright 2019 Matthew Bellafaire.
Licensed under the MIT license:

    http://www.opensource.org/licenses/mit-license.php

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <BatteryMonitor.h>

/*  in order to measure the battery voltage consistently the arduino must use its own internal 
 *   voltage reference. To use this library a capacitor MUST be attached between the AREF pin and
 *   ground.  
 */
BatteryMonitor bat = BatteryMonitor(A1);

void setup() {
  /*Configuring voltage divider connected to ADC pin, any values can be used here
     but it is recommended that R2/(R1 + R2) < 0.2
     default values are 20K for R1 and 4.7K for R2
  */
  bat.setR1(20000);
  bat.setR2(4700);

  /*Configuring the thresholds for battery voltage
      Defaults are:
         lowVoltage = 3.2;
         highVoltage = 4.5;
         criticalVoltage = 2.8;
  */
  bat.setLowVoltage(3.3);
  bat.setCriticalVoltage(3.0);
  bat.setHighVoltage(4.3);
}

void loop() {
  if (bat.isGood()) {
    //TODO if battery voltage is good
  } else if (bat.isLow()) {
    //TODO if battery voltage is low
  } else if (bat.isCritical()) {
    //TODO if battery voltgae is critical
  } else {
    //TODO if battery voltage is high
  }
}



