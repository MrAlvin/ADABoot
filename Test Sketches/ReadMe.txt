For testing boot loaders, I use these sketches. 
After being loaded, they each give a serial output.


Hello_World_Blink
-----------------
Is an extended "Blink" sketch that 
   - blinks LED on 13
   - takes a reading on an analog port, and
   - sets PWM (analogWrite) on a port, and
   - sends data to the serial interface
   - says "Hello World" on a LCD (if connected) and counts seconds

This way there are several ways to see if the sketch compiles, loads and runs.


Sleep_Serial_WDT
----------------
This sketch:
   - waits for 10 seconds for use input from the serial port (options: "S" or "A")
   - countdown on the serial monitor for ten seconds
   - on "S" input or after 10 seconds, the Arduino will be put to sleep
   - after about two seconds of sleep, the WDT (Watch Dog Timer) will wake up and reset the Arduino
   - and a reboot of the Arduino happens


FuseBytes
----------
A sketch by WestFW (see github.com/westfw) that once loaded and run,
will send information about the AVR chip to the serial port

