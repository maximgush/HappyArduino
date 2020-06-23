/*
  Заглушки для функций из Print.h из библиотеки Arduino
  Оригинальный файл находится здесь:
  https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Print.h
*/

#pragma once

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
	#undef BIN
#endif
#define BIN 2