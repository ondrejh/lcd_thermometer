msp430fr4133 launchpad multipoint thermometer with lcd
======================================================

To do:

	- use timer instead of busy wait
	- add UART support with some suitable protocol (modbus?)
	- use buttons to switch between endpoints

GCC project for msp430fr4133 launchpad. DS18B20 driver, LCD output.

Included:

    - LCD driver lcd_e.c, lcd_e.h taken from TI example sources
	- LCD API lcd.c, lcd.h for driving the integrated LCD.
	- DS18B20 driver.
	- GCC makefile
	- Code:Blocks project file

Usage:

	Type "make" to compile the binary.
	Type "make program" ("make program_win") to flash it to the launchpad.
