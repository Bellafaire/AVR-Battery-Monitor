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
#include<avr/delay.h>

class BatteryMonitor {
  public:
    BatteryMonitor(int AnalogPin);
    BatteryMonitor(int AnalogPin, float lowVoltage, float highVoltage);
    BatteryMonitor(int AnalogPin, float lowVoltage, float highVoltage, long R1, long R2);
    void checkBattery();
    void setGoodNotificationPin(int pin);
    void setLowNotificationPin(int pin);
    void setLowVoltage(float voltage);
    void setHighVoltage(float voltage);
    void setCriticalVoltage(float voltage);
    void setR1(long value);
    void setR2(long value);
	bool isGood(); 
	bool isLow();
	bool isCritical();
	bool isHigh();
    float getCurrentBatteryVoltage(int adcRead);
  private:
    float getVoltageDividerFactor();
    void highVoltage();
    void voltageGood();
    void lowVoltage();
    void criticalVoltage();
    int readADC();
    long _R1 = 20000;
    long _R2 = 4700;
    float _lowVoltage = 3.2;
    float _highVoltage = 4.5;
    float _criticalVoltage = 2.8;
    int _goodNotificationPin;
    int _lowNotificationPin;
    int _analogPin;
};


#endif