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

#define batVoltagePin A0 //connect directly to positive terminal of the battery
#define batCurrentPin A1 //connect to the other side of a shunt resistor going from the positive battery terminal to the rest of your circuit

BatteryMonitor bat = BatteryMonitor(batVoltagePin, batCurrentPin);

void setup(){
  /* You can use whatever shunt resistor you want to as long as it supplies your
   * circuit. however current reading resolution is reduced significantly below 0.05 ohms, so going lower
   * than that is not recomended. 
   */
  bat.setCurrentSenseResistance(0.05);
}

void loop() {

  if(bat.getBatteryCurrent() > 1){
    //something to do if current is greater than 1 Amp
  }
  if(bat.getBatteryCurrent() < .2){
    //something to do if current is less than 200ma
  }

}



