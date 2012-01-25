# Makefile for ADABoot modified from ATmegaBOOT
# 
# $Id$
#
#------------------------------------------------------------
#
# Brian B Riley  <brianbr@wulfden.org>  -- BBR
#
# 20120114: Modfified for ADAboot for 1280 (MrAlvin)
# 20090413: Modfified for ADAboot for 644P (BBR)
# 20090325: Modified for the ADABoot for 168 and 328 (BBR) 
# 20050718: Created - E. Lins
#
# Instructions
#
#  make atmega168       - compile for 168
#
#  make atmega168_isp   - burn bootloader with ISP
#
#  make atmega328p      - compile for 328
#
#  make atmega328p_isp  - burn bootloader with ISP
#
#  (suggestions for 644 and 324p, but they are not implemented yet
#    need Fuse settings for 644 and 324p -- BBR
#
#  make atmega644p      - compile for 644p (alternately use 644 or 324p)
#
#  make atmega644p_isp  - burn bootloader with ISP (alternately use 644 or 324p)
#
#------------------------------------------------------------
#
# - if changes made only to Makefile, remember to "touch *.c"
#   to force make to recompile -- BBR
#
#------------------------------------------------------------
#
#

# program name should not be changed...
PROGRAM    = ATmegaBOOT_168

# enter the parameters for the avrdude isp tool
ISPTOOL	   = stk500v2
ISPPORT	   = usb
ISPSPEED   = -b 115200

MCU_TARGET = atmega168
LDSECTION  = --section-start=.text=0x3800

# the efuse should really be 0xf8; since, however, only the lower
# three bits of that byte are used on the atmega168, avrdude gets
# confused if you specify 1's for the higher bits, see:
# http://tinker.it/now/2007/02/24/the-tale-of-avrdude-atmega168-and-extended-bits-fuses/
#
# similarly, the lock bits should be 0xff instead of 0x3f (to
# unlock the bootloader section) and 0xcf instead of 0x0f (to
# lock it), but since the high two bits of the lock byte are
# unused, avrdude would get confused.

ISPFUSES    = avrdude -c $(ISPTOOL) -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
-e -u -U lock:w:0x3f:m -U efuse:w:0x$(EFUSE):m -U hfuse:w:0x$(HFUSE):m -U lfuse:w:0x$(LFUSE):m
ISPFLASH    = avrdude -c $(ISPTOOL) -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
-U flash:w:$(TARGET).hex -U lock:w:0x0f:m

STK500 = "C:\Program Files\Atmel\AVR Tools\STK500\Stk500.exe"
STK500-1 = $(STK500) -e -d$(MCU_TARGET) -pf -vf -if$(TARGET).hex \
-lFF -LFF -f$(HFUSE)$(LFUSE) -EF8 -ms -q -cUSB -I200kHz -s -wt
STK500-2 = $(STK500) -d$(MCU_TARGET) -ms -q -lCF -LCF -cUSB -I200kHz -s -wt


OBJ        = $(PROGRAM).o
OPTIMIZE   = -O2

DEFS       = 
LIBS       =

CC         = avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS       = -Wl,$(LDSECTION)
#override LDFLAGS       = -Wl,-Map,$(PROGRAM).map,$(LDSECTION)

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all:

#####    From here  - section copied in from Sanguino-0023r2   ######

lilypad: TARGET = lilypad
lilypad: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>1' '-DNUM_LED_FLASHES=3'
lilypad: AVR_FREQ = 8000000L
lilypad: ADABoot_lilypad.hex

lilypad_isp: lilypad
lilypad_isp: TARGET = lilypad
lilypad_isp: HFUSE = DD
lilypad_isp: LFUSE = E2
lilypad_isp: EFUSE = 00
lilypad_isp: isp

lilypad_resonator: TARGET = lilypad_resonator
lilypad_resonator: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=3'
lilypad_resonator: AVR_FREQ = 8000000L
lilypad_resonator: ADABoot_lilypad_resonator.hex

lilypad_resonator_isp: lilypad_resonator
lilypad_resonator_isp: TARGET = lilypad_resonator
lilypad_resonator_isp: HFUSE = DD
lilypad_resonator_isp: LFUSE = C6
lilypad_resonator_isp: EFUSE = 00
lilypad_resonator_isp: isp

pro8: TARGET = pro_8MHz
pro8: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=1' '-DWATCHDOG_MODS'
pro8: AVR_FREQ = 8000000L
pro8: ADABoot_pro_8MHz.hex

pro8_isp: pro8
pro8_isp: TARGET = pro_8MHz
pro8_isp: HFUSE = DD
pro8_isp: LFUSE = C6
pro8_isp: EFUSE = 00
pro8_isp: isp

pro16: TARGET = pro_16MHz
pro16: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=1' '-DWATCHDOG_MODS'
pro16: AVR_FREQ = 16000000L
pro16: ADABoot_pro_16MHz.hex

pro16_isp: pro16
pro16_isp: TARGET = pro_16MHz
pro16_isp: HFUSE = DD
pro16_isp: LFUSE = C6
pro16_isp: EFUSE = 00
pro16_isp: isp

pro20: TARGET = pro_20mhz
pro20: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=1' '-DWATCHDOG_MODS'
pro20: AVR_FREQ = 20000000L
pro20: ADABoot_pro_20mhz.hex

pro20_isp: pro20
pro20_isp: TARGET = pro_20mhz
pro20_isp: HFUSE = DD
pro20_isp: LFUSE = C6
pro20_isp: EFUSE = 00
pro20_isp: isp

diecimila: TARGET = diecimila
diecimila: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=1'
diecimila: AVR_FREQ = 16000000L 
diecimila: ADABoot_diecimila.hex

diecimila_isp: diecimila
diecimila_isp: TARGET = diecimila
diecimila_isp: HFUSE = DD
diecimila_isp: LFUSE = FF
diecimila_isp: EFUSE = 00
diecimila_isp: isp

ng: TARGET = ng
ng: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>1' '-DNUM_LED_FLASHES=3'
ng: AVR_FREQ = 16000000L
ng: ADABoot_ng.hex

ng_isp: ng
ng_isp: TARGET = ng
ng_isp: HFUSE = DD
ng_isp: LFUSE = FF
ng_isp: EFUSE = 00
ng_isp: isp


atmega328_pro8: TARGET = atmega328_pro_8MHz
atmega328_pro8: MCU_TARGET = atmega328p
atmega328_pro8: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=1' -DBAUD_RATE=57600 -DDOUBLE_SPEED
atmega328_pro8: AVR_FREQ = 8000000L 
atmega328_pro8: LDSECTION  = --section-start=.text=0x7800
atmega328_pro8: ADABoot_atmega328p_pro_8MHz.hex

atmega328_pro8_isp: atmega328_pro8
atmega328_pro8_isp: TARGET = atmega328_pro_8MHz
atmega328_pro8_isp: MCU_TARGET = atmega328p
atmega328_pro8_isp: HFUSE = DA
atmega328_pro8_isp: LFUSE = FF
atmega328_pro8_isp: EFUSE = 05
atmega328_pro8_isp: isp

#####    To Here   -  section copied in from Sanguino-0023r2   ########
#########  compiles fine, but needs testing on actual chip : 2012-01-24


atmega168: TARGET = atmega168
atmega168: MCU_TARGET = atmega168
atmega168: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DADABOOT=4' '-DWATCHDOG_MODS'
atmega168: AVR_FREQ = 16000000L 
atmega168: LDSECTION  = --section-start=.text=0x3800
atmega168: ADABoot_168.hex

atmega168_isp: atmega168
atmega168_isp: TARGET = ADABoot_168
atmega168_isp: MCU_TARGET = atmega168
atmega168_isp: HFUSE = DD
atmega168_isp: LFUSE = FF
atmega168_isp: EFUSE = 00
atmega168_isp: isp

atmega328p: TARGET = atmega328
atmega328p: MCU_TARGET = atmega328p
atmega328p: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DBAUD_RATE=57600' '-DADABOOT=4' '-DWATCHDOG_MODS'
atmega328p: AVR_FREQ = 16000000L 
atmega328p: LDSECTION  = --section-start=.text=0x7800
atmega328p: ADABoot_328.hex

atmega328p_isp: atmega328p
atmega328p_isp: TARGET = ADABoot_328
atmega328p_isp: MCU_TARGET = atmega328p
atmega328p_isp: HFUSE = DA
atmega328p_isp: LFUSE = FF
atmega328p_isp: EFUSE = 05
atmega328p_isp: isp

atmega644p: TARGET = atmega644p
atmega644p: MCU_TARGET = atmega644p
atmega644p: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DBAUD_RATE=38400' '-DADABOOT=4' '-DWATCHDOG_MODS'
atmega644p: AVR_FREQ = 16000000L 
atmega644p: LDSECTION  = --section-start=.text=0xF800
atmega644p: ADABoot_644p.hex

atmega644p_isp: atmega644p
atmega644p_isp: TARGET = ADABoot_644p
atmega644p_isp: MCU_TARGET = atmega644p
atmega644p_isp: HFUSE = DC
atmega644p_isp: LFUSE = FF
atmega644p_isp: EFUSE = FD
atmega644p_isp: isp

mega: TARGET = atmega1280
mega: MCU_TARGET = atmega1280
mega: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=0' -DBAUD_RATE=57600 '-DADABOOT=4' '-DWATCHDOG_MODS'
mega: AVR_FREQ = 16000000L 
mega: LDSECTION  = --section-start=.text=0x1F000
mega: ADABoot_1280.hex

mega_isp: mega
mega_isp: TARGET = atmega1280
mega_isp: MCU_TARGET = atmega1280
mega_isp: HFUSE = DA
mega_isp: LFUSE = FF
mega_isp: EFUSE = F5
mega_isp: isp


# compiles fine, but needs testing on actual chip : 2012-01-24
atmega1284p: TARGET = atmega1284p
atmega1284p: MCU_TARGET = atmega1284p
atmega1284p: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=0' '-DBAUD_RATE=57600'
atmega1284p: AVR_FREQ = 16000000L 
atmega1284p: LDSECTION  = --section-start=.text=0x1F800
atmega1284p: $(PROGRAM)_atmega1284p.hex

atmega1284p_isp: atmega1284p
atmega1284p_isp: TARGET = atmega1284p
atmega1284p_isp: MCU_TARGET = atmega1284p
atmega1284p_isp: HFUSE = DC
atmega1284p_isp: LFUSE = FF
atmega1284p_isp: EFUSE = FD
atmega1284p_isp: isp

isp: $(TARGET)
	$(ISPFUSES)
	$(ISPFLASH)

isp-stk500: $(TARGET).hex
	$(STK500-1)
	$(STK500-2)

%.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@
	
