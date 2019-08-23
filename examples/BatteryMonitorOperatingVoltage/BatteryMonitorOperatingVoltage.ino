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

/*  Measuring the operating voltage of the arduino may be useful in situations where the 
 *   arduino itself is powered by a boost converter in circuit or otherwise used to control an 
 *   external boost converter. 
 *   
 *   NOTE: if the arduino is powered directly from the battery then the AREF pin should be connected
 *   directly to the positive terminal of the battery before the shunt resistor (if you're using one). if the
 *   arduino is being powered from a boost converter connected to the battery than AREF should be connected to the output 
 *   of the boost converter.
 *   
 *   Essentially AREF should always be attached to the highest voltage in the circuit provided that it does not exceed 5.5V  
 */

 //init a BatteryMonitor object and set the voltage measuring pin to our defenition above.
BatteryMonitor bat = BatteryMonitor(batVoltagePin);

void setup() {

}

void loop() {
  if (bat.getCurrentBatteryVoltage() < 3.0) {
    //something to do if the battery voltage is below 3.0v
    }
  if(bat.getCurrentOperatingVoltage() < 4.0){
    //something to do if the operating voltage is less than 4 volts. 
  }
}



