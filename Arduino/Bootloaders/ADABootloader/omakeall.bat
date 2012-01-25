@ECHO OFF
REM   Use this for building ADABoot on windows for all defined AVRs
REM
REM   Copy ADABootLoader folder to ..arduino-1.0-windows\arduino-1.0\hardware\arduino\bootloaders
REM
REM   To use, open Command Prompt and move to  C:\...\hardware\arduino\bootloaders
REM   there use command:  omake atmega328
REM   to compile the ADABoot bootloader for the ATmega328p
REM
@ECHO ON
CALL omake clean
CALL omake atmega168
CALL omake atmega328p
CALL omake atmega644p
CALL omake mega   
CALL omake lilypad
CALL omake lilypad_resonator 
CALL omake pro8 
CALL omake pro16 
CALL omake pro20 
CALL omake diecimila   
CALL omake ng 
CALL omake atmega328_pro8 
CALL omake atmega1284p  
     
REM CALL omake atmega328bb   (untested)