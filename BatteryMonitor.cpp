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

#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor(int AnalogPin) {
  _analogPin = AnalogPin;
}

BatteryMonitor::BatteryMonitor(int AnalogPin, float lowVoltage, float criticalVoltage) {
  _analogPin = AnalogPin;
  _lowVoltage = lowVoltage;
  _criticalVoltage = criticalVoltage;
}

BatteryMonitor::BatteryMonitor(int AnalogPin, float lowVoltage, float criticalVoltage, long R1, long R2) {
  _analogPin = AnalogPin;
  _lowVoltage = lowVoltage;
  _criticalVoltage = criticalVoltage;
  _R1 = R1;
  _R2 = R2;
}


int BatteryMonitor::readADC() {
  ADMUX &= 0b00110000;
  ADMUX |= 0b11000000;

  switch (_analogPin) {
    case A0: ADMUX |= 0b00000000; break;
    case A1: ADMUX |= 0b00000001; break;
    case A2: ADMUX |= 0b00000010; break;
    case A3: ADMUX |= 0b00000011; break;
    case A4: ADMUX |= 0b00000100; break;
    case A5: ADMUX |= 0b00000101; break;
    case A6: ADMUX |= 0b00000110; break;
    case A7: ADMUX |= 0b00000111; break;
  }

  ADCSRA |= (1 << ADEN) | (1 << ADSC);
  while (ADCSRA & (1 << ADSC)) {
    delayMicroseconds(10);
  }
  int ret = 0;
  ret |= ADCL;
  ret |= (ADCH << 8);
  
  return ret;
}

float BatteryMonitor::getVoltageDividerFactor() {
  return ((float)_R2) / ((float)_R1 + (float)_R2);
}

float BatteryMonitor::getCurrentBatteryVoltage() {
  float voltstep = 1.1 / 1024;
  float adcReadVoltage = voltstep * readADC();
  return adcReadVoltage / getVoltageDividerFactor();
}

void BatteryMonitor::checkBattery() {
  float batVoltage = getCurrentBatteryVoltage();
  if (batVoltage > _highVoltage) {
    highVoltage();
  } else if (batVoltage > _lowVoltage ) {
    voltageGood();
  } else if (batVoltage > _criticalVoltage) {
    lowVoltage();
  } else {
    criticalVoltage();
  }
}

bool BatteryMonitor::isGood() {
  float batVoltage = getCurrentBatteryVoltage();
  return (batVoltage > _lowVoltage && batVoltage < _highVoltage);
}
bool BatteryMonitor::isLow() {
  float batVoltage = getCurrentBatteryVoltage();
  return (batVoltage > _criticalVoltage && batVoltage < _lowVoltage);
}
bool BatteryMonitor::isCritical() {
  float batVoltage = getCurrentBatteryVoltage();
  return (batVoltage < _criticalVoltage);
}
bool BatteryMonitor::isHigh() {
  float batVoltage = getCurrentBatteryVoltage();
  return (batVoltage > _highVoltage);
}

void BatteryMonitor::highVoltage() {
  if (_goodNotificationPin != NULL) {
    digitalWrite(_goodNotificationPin, HIGH);
  }
  if (_lowNotificationPin != NULL) {
    digitalWrite(_lowNotificationPin, HIGH);
  }
}
void  BatteryMonitor::voltageGood() {
  if (_goodNotificationPin != NULL) {
    digitalWrite(_goodNotificationPin, HIGH);
  }
  if (_lowNotificationPin != NULL) {
    digitalWrite(_lowNotificationPin, LOW);
  }
}
void BatteryMonitor::lowVoltage() {
  if (_goodNotificationPin != NULL) {
    digitalWrite(_goodNotificationPin, LOW);
  }
  if (_lowNotificationPin != NULL) {
    digitalWrite(_lowNotificationPin, HIGH);
  }
}
void BatteryMonitor::criticalVoltage() {
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  //clear all outputs
  PORTB = 0b00000000;
  PORTC = 0b00000000;
  PORTD = 0b00000000;
  sleep_cpu();
}

void BatteryMonitor::setGoodNotificationPin(int pin) {
  _goodNotificationPin = pin;
  pinMode(pin, OUTPUT);
}

void BatteryMonitor::setLowNotificationPin(int pin) {
  _lowNotificationPin = pin;
  pinMode(pin, OUTPUT);
}

void BatteryMonitor::setLowVoltage(float voltage) {
  _lowVoltage = voltage;
}

void BatteryMonitor::setCriticalVoltage(float voltage) {
  _criticalVoltage = voltage;
}

void BatteryMonitor::setHighVoltage(float voltage) {
  _highVoltage = voltage;
}

void BatteryMonitor::setR1(long value) {
  _R1 = value;
}

void BatteryMonitor::setR2(long value) {
  _R2 = value;
}