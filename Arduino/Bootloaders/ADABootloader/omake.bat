@ECHO OFF
REM   Use this for building ADABoot on windows
REM   Copy ADABootLoader folder to ..arduino-1.0-windows\arduino-1.0\hardware\arduino\bootloaders\
REM
REM   To use, open Command Prompt and move to  C:\...\hardware\arduino\bootloaders\adabootloader
REM   there use command:  omake atmega328
REM   to compile the ADABoot bootloader for the ATmega328p
REM
@ECHO ON
..\..\..\tools\avr\utils\bin\make OS=windows ENV=arduino %*
