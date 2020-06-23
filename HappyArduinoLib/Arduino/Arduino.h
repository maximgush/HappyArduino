/*
  Заглушки для функций из Arduino.h
  Оригинальный файл находится здесь:
  https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h
*/
#pragma once

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
	#undef BIN
#endif
#define BIN 2

#include <cstdint>

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3
/*
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))
*/
#define interrupts() sei()
#define noInterrupts() cli()

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

void init( void ) {}
void initVariant( void ) {}

//int atexit( void( *func )( ) ) __attribute__( ( weak ) );

void pinMode( uint8_t pin, uint8_t mode ) {};
void digitalWrite( uint8_t pin, uint8_t val ) {};
int digitalRead( uint8_t pin ) { return 0; }
int analogRead( uint8_t pin ) { return 0; }
void analogReference( uint8_t mode ) {}
void analogWrite( uint8_t pin, int val ) {}

unsigned long millis( void ) { return 0; }
unsigned long micros( void ) { return 0; }
void delay( unsigned long ms ) {}
void delayMicroseconds( unsigned int us ) {}
unsigned long pulseIn( uint8_t pin, uint8_t state, unsigned long timeout = 1000000L ) { return 0; }
unsigned long pulseInLong( uint8_t pin, uint8_t state, unsigned long timeout = 1000000L ) { return 0; }

void shiftOut( uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val ) {}
uint8_t shiftIn( uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder ) { return 0; }

void attachInterrupt( uint8_t interruptNum, void( *userFunc )( void ), int mode ) {}
void detachInterrupt( uint8_t interruptNum ) {}

void setup( void ) {}
void loop( void ) {}

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.

// WMath prototypes
long random( long ) { return 0; }
long random( long, long ) { return 0; }
void randomSeed( unsigned long ) {};
long map( long, long, long, long, long ) { return 0; }