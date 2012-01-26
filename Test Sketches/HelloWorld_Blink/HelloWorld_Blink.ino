/*
  Blink example - modified to not use the delay command, but to test blink time using millis()
  
        combined with
  
  LiquidCrystal Library - Hello World - for LCD I/O Backpack by hackmeister.dk
 
        and
        
    
      
 LiquidCrystal Library:
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

//Basic Blink example, but without the use of delay()
int blink_pin = 13;
int on_delay = 1000;
int off_delay = 1000;
long blink_millis;
boolean do_on = true;

//Analog Read and Serial Out example, but without the use of delay()
long analog_millis;
int analog_delay = 10;

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A7;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


//LCD example
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);   //LCD I/O Backpack default



void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  
  // initialize the digital blink pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(blink_pin, OUTPUT);  
  
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {

  //LCD example  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);


//Blink example
  if (blink_millis <= millis() )  // if its time to change the blink
  { 
    if (do_on)  //use a flag to determine wether to turn on or off the Blink LED
    {
      digitalWrite(blink_pin, HIGH);   // set the LED on
      blink_millis = millis() + off_delay; // wait for a second
      do_on = false;
    } 
    else
    {
      digitalWrite(blink_pin, LOW);    // set the LED off
      blink_millis = millis() + on_delay;
      do_on = true;
    } 
  }

//Analog Read and Serial out example  
  if (analog_millis <= millis() )  // if its time to make a new reading
  { 
    // read the analog in value:
    sensorValue = analogRead(analogInPin);            
    // map it to the range of the analog out:
    outputValue = map(sensorValue, 0, 1023, 0, 255);  
    // change the analog out value:
    analogWrite(analogOutPin, outputValue);           
  
    // print the results to the serial monitor:
    Serial.print("sensor = " );                       
    Serial.print(sensorValue);      
    Serial.print("\t output = ");      
    Serial.println(outputValue);   

    // wait 10 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    // delay(10);            
    analog_millis = millis() + analog_delay;
  }
}


