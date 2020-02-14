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

BatteryMonitor::BatteryMonitor(int batteryPin) {
  _batPin = batteryPin;
  pinMode(batteryPin, INPUT);
}

BatteryMonitor::BatteryMonitor(int batteryPin, int currentSensePin) {
  _batPin = batteryPin;
  pinMode(batteryPin, INPUT);
  _sensePin = currentSensePin;
  pinMode(_sensePin, INPUT);
}

float BatteryMonitor::getBatteryCurrent() {
	#if defined(__AVR_ATtiny85__) || (__AVR_ATtiny45__) || (__AVR_ATtiny25__)
		//so we do the same calculations but we perform them with integers instead to save memory 

		int v = readBatteryVoltage() - readCurrentSense();
		v = v * 11000;
		int d = readReference() * (int)(_senseResistance * 100);
		
		return (float)(v / (d * 10));
		
	#else
  return ((1.1 * ((float)readBatteryVoltage() - (float)readCurrentSense())) / ((float)readReference() * (float)_senseResistance));
	#endif
 
}


void BatteryMonitor::setCurrentSensePin(int currentSensePin) {
  _sensePin = currentSensePin; pinMode(_sensePin, INPUT);

}
void BatteryMonitor::setCurrentSenseResistance(float r) {
  _senseResistance = r;
}

int BatteryMonitor::readCurrentSense() {
  selectPin(_sensePin);
  
  ADCSRA |= (1 << ADEN) | (1 << ADSC);
  while (ADCSRA & (1 << ADSC)) {
  }

  int val = 0;
  val |= ADCL;
  val |= (ADCH << 8);
  return val;

}

int BatteryMonitor::readBatteryVoltage() {

  selectPin(_batPin);
  
  ADCSRA |= (1 << ADEN) | (1 << ADSC);
  while (ADCSRA & (1 << ADSC)) {
  }

  int val = 0;
  val |= ADCL;
  val |= (ADCH << 8);
  return val;

}

void BatteryMonitor::selectPin(int pin) {
	#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
  if(_VCCREF){
  ADMUX = 0b01000000;
  }
  else{
	  ADMUX = 0b00000000;
  }
	switch (pin) {
    case A0: ADMUX |= 0b00000000; break;
    case A1: ADMUX |= 0b00000001; break;
    case A2: ADMUX |= 0b00000010; break;
    case A3: ADMUX |= 0b00000011; break;
    case A4: ADMUX |= 0b00000100; break;
    case A5: ADMUX |= 0b00000101; break;
    case A6: ADMUX |= 0b00000110; break;
    case A7: ADMUX |= 0b00000111; break;
  }
  
  #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  
  //#error "ATMEGA1280/2560 not currently supported by library, sorry.
  
  #elif defined(__AVR_ATtiny85__) || (__AVR_ATtiny45__) || (__AVR_ATtiny25__)
  if(_VCCREF){
  ADMUX = 0b01000000;
  }
  else{
	  ADMUX = 0b00000000;
  }
  switch (pin) {
    case A0: ADMUX |= 0b00000000; break;
    case A1: ADMUX |= 0b00000001; break;
    case A2: ADMUX |= 0b00000010; break;
  }
  
  #endif
	
}

int BatteryMonitor::readReference() {

  //set adc to use AREF as reference then select the internal reference as our ideal read
  if(_VCCREF){
  ADMUX = 0b01001110;
  }
  else{
	  ADMUX = 0b00001110;
  }
  delay(10);

  ADCSRA |= (1 << ADEN) | (1 << ADSC);
  while (ADCSRA & (1 << ADSC)) {
  }

  int ref = 0;
  ref |= ADCL;
  ref |= (ADCH << 8);
  return ref;

}

void BatteryMonitor::refVCC(boolean b){
	_VCCREF = b;
}

float BatteryMonitor::getCurrentBatteryVoltage() {
	#if defined(__AVR_ATtiny85__) || (__AVR_ATtiny45__) || (__AVR_ATtiny25__)
		//so we do the same calculations but we perform them with integers instead to save memory 
		
		int v = 11 * readBatteryVoltage();
		v = v / readReference();
		
		return ((float)v)/10;
	#else
  return (((float)1.1 * (float)readBatteryVoltage()) / (float)readReference());
	#endif
}

float BatteryMonitor::getCurrentOperatingVoltage() {
		#if defined(__AVR_ATtiny85__) || (__AVR_ATtiny45__) || (__AVR_ATtiny25__)
	
		int v = 11 * 1024;
			v = v / readReference();
		
		return ((float)v)/10;
	
	#else
  return (((float)1.1 * (float)1024) / (float)readReference());
	#endif
}