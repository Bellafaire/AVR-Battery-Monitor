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

#define RED_LED 2
#define BLUE_LED 3

/*  in order to measure the battery voltage consistently the arduino must use its own internal
     voltage reference. To use this library a capacitor MUST be attached between the AREF pin and
     ground.
*/

//simple constructor, only requires the analog pin which will monitor the battery's + terminal
BatteryMonitor bat = BatteryMonitor(A0);

/*    all constructors available
    BatteryMonitor(int AnalogPin);
    BatteryMonitor(int AnalogPin, float lowVoltage, float highVoltage);
    BatteryMonitor(int AnalogPin, float lowVoltage, float highVoltage, long R1, long R2);
*/
void setup() {
  /* setting the notification LED's to communicate status
     of the battery voltage to the user, the good notification will
     be lit when the battery voltage is good, the low notification will be
     lit when the battery voltage is low but not critical.
  */
//  bat.setGoodNotificationPin(BLUE_LED);
//  bat.setLowNotificationPin(RED_LED);

  /*Configuring the thresholds for battery voltage
      Defaults are:
         lowVoltage = 3.2;
         highVoltage = 4.5;
         criticalVoltage = 2.8;
//  */
//  bat.setLowVoltage(3.3);
//  bat.setCriticalVoltage(3.0);
//  bat.setHighVoltage(4.3);

bat.setCurrentSenseResistance(1.2);
bat.setCurrentSensePin(A1); 


  Serial.begin(9600);
}

void loop() {
  /*  checks battery and uses default actions
        battery high = battery good and battery low notifiication pin HIGH
        battery good = battery good notification pin HIGH
        battery low = battery low notifiication pin HIGH
        battery critical = arduino goes into deep sleep
  */

Serial.println(bat.getCurrentBatteryVoltage());
}



