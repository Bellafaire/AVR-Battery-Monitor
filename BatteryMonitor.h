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

#ifndef BatteryMonitor_h
#define BatteryMonitor_h

#include "Arduino.h"
#include <avr/sleep.h>
#include<avr/io.h>
#include<util/delay.h>

class BatteryMonitor {
  public:
    BatteryMonitor(int batteryPin);
    BatteryMonitor(int batteryPin, int currentSensePin);
    void setCurrentSensePin(int currentSensePin);
    void setCurrentSenseResistance(float r);
    float getCurrentBatteryVoltage();
	float getCurrentOperatingVoltage();
    float getBatteryCurrent();
	void refVCC(boolean b);
	
  private: 
	int readBatteryVoltage();
	void selectPin(int pin);
    int readReference();
	int readCurrentSense();
    
	//class variables
	float _senseResistance = 0.05;
	int _batPin;
    int _sensePin;
	boolean _VCCREF = true;
};


#endif