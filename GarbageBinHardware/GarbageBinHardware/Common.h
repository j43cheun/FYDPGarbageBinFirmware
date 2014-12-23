/*
 * Common.h
 *
 * Created: 2014-12-21 10:44:57 PM
 *  Author: Justin
 */ 

#ifndef COMMON_H_
#define COMMON_H_

#define F_CPU            16000000L

#define ClearBit( x, y ) x &= ~_BV( y );
#define SetBit( x, y )   x |= _BV( y );

#include <avr/io.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <util/delay.h>

#endif /* COMMON_H_ */