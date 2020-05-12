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



BatteryMonitor::BatteryMonitor(int batteryPin)
{
  _batPin = batteryPin;
  pinMode(batteryPin, INPUT);
}

BatteryMonitor::BatteryMonitor(int batteryPin, int currentSensePin)
{
  _batPin = batteryPin;
  pinMode(batteryPin, INPUT);
  _sensePin = currentSensePin;
  pinMode(_sensePin, INPUT);
}

float BatteryMonitor::getBatteryCurrent()
{
  return ((1.1 * ((float)readBatteryVoltage() - (float)readCurrentSense())) / ((float)readReference() * (float)_senseResistance));
}

void BatteryMonitor::setCurrentSensePin(int currentSensePin)
{
  _sensePin = currentSensePin;
  pinMode(_sensePin, INPUT);
}
void BatteryMonitor::setCurrentSenseResistance(float r)
{
  _senseResistance = r;
}

int BatteryMonitor::readCurrentSense()
{

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = 0b00000000;
  switch (_sensePin)
  {
  case PB2:
    ADMUX |= 0b00000001;
    break;
  case PB3:
    ADMUX |= 0b00000011;
    break;
  case PB4:
    ADMUX |= 0b00000010;
    break;
  case PB5:
    ADMUX |= 0b00000000;
    break;
  }
#else

  if (useVCCasREF)
  {
    //set VCC as reference for reading the battery voltage
    ADMUX = 0b01000000;
  }
  else
  {
    //use aref as reference
    ADMUX = 0b00000000;
  }

  switch (_sensePin)
  {
  case A0:
    ADMUX |= 0b00000000;
    break;
  case A1:
    ADMUX |= 0b00000001;
    break;
  case A2:
    ADMUX |= 0b00000010;
    break;
  case A3:
    ADMUX |= 0b00000011;
    break;
  case A4:
    ADMUX |= 0b00000100;
    break;
  case A5:
    ADMUX |= 0b00000101;
    break;
  case A6:
    ADMUX |= 0b00000110;
    break;
  case A7:
    ADMUX |= 0b00000111;
    break;
  }
#endif
  ADCSRA |= (1 << ADEN) | (1 << ADSC);
  while (ADCSRA & (1 << ADSC))
  {
    delayMicroseconds(10);
  }

  int val = 0;
  val |= ADCL;
  val |= (ADCH << 8);
  return val;
}

int BatteryMonitor::readBatteryVoltage()
{

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  //set adc to use VCC as reference
  ADMUX = 0b00000000;
  switch (_sensePin)
  {
  case PB2:
    ADMUX |= 0b00000001;
    break;
  case PB3:
    ADMUX |= 0b00000011;
    break;
  case PB4:
    ADMUX |= 0b00000010;
    break;
  case PB5:
    ADMUX |= 0b00000000;
    break;
  }
#else
  if (useVCCasREF)
  {
    //set VCC as reference for reading the battery voltage
    ADMUX = 0b01000000;
  }
  else
  {
    //use aref as reference
    ADMUX = 0b00000000;
  }
  switch (_sensePin)
  {
  case A0:
    ADMUX |= 0b00000000;
    break;
  case A1:
    ADMUX |= 0b00000001;
    break;
  case A2:
    ADMUX |= 0b00000010;
    break;
  case A3:
    ADMUX |= 0b00000011;
    break;
  case A4:
    ADMUX |= 0b00000100;
    break;
  case A5:
    ADMUX |= 0b00000101;
    break;
  case A6:
    ADMUX |= 0b00000110;
    break;
  case A7:
    ADMUX |= 0b00000111;
    break;
  }
#endif

  ADCSRA |= (1 << ADEN) | (1 << ADSC);
  while (ADCSRA & (1 << ADSC))
  {
    delayMicroseconds(10);
  }

  int val = 0;
  val |= ADCL;
  val |= (ADCH << 8);
  return val;
}

int BatteryMonitor::readReference()
{
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = 0;           //reset ADMUX
  ADMUX |= 0b00001100; //use vcc as reference and select V_BG to read reference
  delay(10);
#else
  if (useVCCasREF)
  {
    //set VCC as reference for reading the battery voltage
    ADMUX = 0b01000000;
  }
  else
  {
    //use aref as reference
    ADMUX = 0b00000000;
  }
  ADMUX |= 0b00001110;
  delay(10);
#endif;

  ADCSRA |= (1 << ADEN) | (1 << ADSC);
  while (ADCSRA & (1 << ADSC))
  {
    delayMicroseconds(10);
  }

  int ref = 0;
  ref |= ADCL;
  ref |= (ADCH << 8);
  return ref;
}

void BatteryMonitor::refVCC(boolean r)
{
  useVCCasREF = r;
}

float BatteryMonitor::getCurrentBatteryVoltage()
{
  return (((float)1.1 * (float)readBatteryVoltage()) / (float)readReference());
}

float BatteryMonitor::getCurrentOperatingVoltage()
{
  return (((float)1.1 * (float)1024) / (float)readReference());
}