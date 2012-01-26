#include <avr/power.h>           // you might get compile errors if not included
#include <avr/interrupt.h>       // you might get compile errors if not included
#include <avr/sleep.h>           // the important one
#include <avr/wdt.h>             // Watch Dog Timer extension

#define BAUD_RATE 9600

/* Sleep Demo Serial
 * -----------------
 * Example code to demonstrate the sleep functions in an Arduino.
 *
 * Enter sleep mode by sending serial "S" or wait 10 seconds
 * Exit sleep mode by connecting pin2 to LOW (GND, 0V)
 * or Watch Dog Timer will also wake up and reset the Arduino after 2 seconds of sleep
 * 
 * Use internal pull-up resistor (default in this example) or use a 
 * resistor between RX and pin2. By default RX is pulled up to 5V in normal
 * serial communication mode. Therefore, we can use a sequence of 
 * Serial data forcing RX to 0, what will make pin2 go LOW 
 * activating INT0 external interrupt, bringing the MCU back to life
 *
 * There is also a time counter that will put the MCU to sleep after 10 secs
 *
 * NOTE: when coming back from POWER-DOWN mode, it takes a bit
 *       until the system is functional at 100%!! (typically <1sec)
 *
 *  Based on Sleep Demo Serial from http://www.arduino.cc/playground/Learning/ArduinoSleepCode 
 *
 * Copyright (C) 2006 MacSimski 2006-12-30 
 * Copyright (C) 2007 D. Cuartielles 2007-07-08 - Mexico DF
 * Copyright (C) 2012 MrAlvin 2012-01-07 - Denmark
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

int wakePin = 2;                   // pin used for waking up
boolean doSleep = false;           // variable/flag to request a sleep state
boolean delayBeforeSleep = false;  // variable/flag to request a sleep state, but wait a little first
int count = 0;                     // counter of awake seconds
long displayDelayTime = 1000;      // update display (and counter) every one second
long displayMillisCount = 0;       // delay counter
long beforeSleepMillisCount = 0;   // delay counter

void wakeUpNow()        // here the interrupt is handled after wakeup
{
  // execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  // we don't really need to execute any special functions here, since we
  // just want the thing to wake up
}

void setup()
{
  pinMode(wakePin, INPUT);     //makeing sure that pin 2 is in interrupt mode
  digitalWrite(wakePin,HIGH);  //activating internal pull-up resistor

  Serial.begin(BAUD_RATE);
  Serial.println("Setup after Reset");

  /* Now it is time to enable an interrupt. In the function call 
   * attachInterrupt(A, B, C)
   * A   can be either 0 or 1 for interrupts on pin 2 or 3.   
   * 
   * B   Name of a function you want to execute while in interrupt A.
   *
   * C   Trigger mode of the interrupt pin. can be:
   *             LOW        a low level trigger
   *             CHANGE     a change in level trigger
   *             RISING     a rising edge of a level trigger
   *             FALLING    a falling edge of a level trigger
   *
   * In all but the IDLE sleep modes only LOW can be used.
   */

  attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                      // wakeUpNow when pin 2 gets LOW 
  wdt_enable(WDTO_2S); // have the wdt reset/wakeup the chip if 2 seconds passes without a call to wdt_reset                                   
}

void sleepNow()         // here we put the arduino to sleep
{
    /* Now is the time to set the sleep mode. In the Atmega8 datasheet
     * http://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf on page 35
     * there is a list of sleep modes which explains which clocks and 
     * wake up sources are available in which sleep mode.
     *
     * In the avr/sleep.h file, the call names of these sleep modes are to be found:
     *
     * The 5 different modes are:
     *     SLEEP_MODE_IDLE         -the least power savings 
     *     SLEEP_MODE_ADC
     *     SLEEP_MODE_PWR_SAVE
     *     SLEEP_MODE_STANDBY
     *     SLEEP_MODE_PWR_DOWN     -the most power savings
     *
     * For now, we want as much power savings as possible, so we 
     * choose the according 
     * sleep mode: SLEEP_MODE_PWR_DOWN
     * 
     */  
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);   // sleep mode is set here

    sleep_enable();          // enables the sleep bit in the mcucr register
                             // so sleep is possible. just a safety pin 

    /* Now it is time to enable an interrupt. We do it here so an 
     * accidentally pushed interrupt button doesn't interrupt 
     * our running program. if you want to be able to run 
     * interrupt code besides the sleep function, place it in 
     * setup() for example.
     * 
     * In the function call attachInterrupt(A, B, C)
     * A   can be either 0 or 1 for interrupts on pin 2 or 3.   
     * 
     * B   Name of a function you want to execute at interrupt for A.
     *
     * C   Trigger mode of the interrupt pin. can be:
     *             LOW        a low level triggers
     *             CHANGE     a change in level triggers
     *             RISING     a rising edge of a level triggers
     *             FALLING    a falling edge of a level triggers
     *
     * In all but the IDLE sleep modes only LOW can be used.
     */

    attachInterrupt(0,wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                       // wakeUpNow when pin 2 gets LOW 

    sleep_mode();            // here the device is actually put to sleep!!
                             // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

    sleep_disable();         // first thing after waking from sleep:
                             // disable sleep...
    detachInterrupt(0);      // disables interrupt 0 on pin 2 so the 
                             // wakeUpNow code will not be executed 
                             // during normal running time.

}

void loop()
{
  updateDisplay();
  processSerial();
  manageSleep();
  wdt_reset(); // reset the watch dog timer
}


void manageSleep()
{
  if (delayBeforeSleep) {
    beforeSleepMillisCount = millis() + 100;  // wait for 100ms until we do sleep
    doSleep = true;  // we want to sleep (when the time is right)
    delayBeforeSleep = false;  // ready for next input
  }
  
  if (doSleep) {
    if (beforeSleepMillisCount - millis() <= 0) { //else wait a little longer
      sleepNow();     // sleep function called here
      doSleep = false; // ready for next time
    }
  }
}


void updateDisplay() 
{
    if (displayMillisCount - millis() <= 0) { //do if one second has passed since last time we were doing it
      displayMillisCount = displayMillisCount + displayDelayTime; // set up the next 1 second wait/delay
      
      // display information about the counter
      Serial.print("Awake for ");
      Serial.print(count);
      Serial.println("sec");
      count++;
    }
}


void processSerial()
{
  // compute the serial input
  if (Serial.available()) {
    int val = Serial.read();
    
    if (val == 'S') {
      Serial.println("Serial: Entering Sleep mode");
      delayBeforeSleep = true;
      //delay(100);     // this delay is needed, the sleep 
                        // function will provoke a Serial error otherwise!!
      count = 0;
    }
    
    if (val == 'A') {
      Serial.println("Hello World"); // classic dummy message
    }
  }

  // check if it should go to sleep because of time
  if (count >= 10) {
      Serial.println("Timer: Entering Sleep mode");
      delayBeforeSleep = true;
      //delay(100);     // this delay is needed, the sleep 
                      //function will provoke a Serial error otherwise!!
      count = 0;
      //sleepNow();     // sleep function called here
  }
}

