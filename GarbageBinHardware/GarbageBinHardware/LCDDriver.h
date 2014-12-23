/*
 * LCDDriver.h
 *
 * Created: 10/4/2014 9:38:10 PM
 *  Author: Justin
 */ 


#ifndef LCDDRIVER_H_
#define LCDDRIVER_H_

#include "Common.h"

typedef uint8_t byte;
typedef int8_t sbyte;

void LCD_PulseEnableLine( void );
void LCD_SendNibble( const byte data );
void LCD_SendByte( const byte data );
void LCD_SendCmd( const byte cmd );
void LCD_SendChar( const byte ch );
void LCD_Init( void );
void LCD_ClearDisplay( void );
void LCD_SetCursorToHome( void );
void LCD_SetCursorTo( const byte x, const byte y );
void LCD_SetCursorToLine( const byte row );
void LCD_PrintMessage( const char *text );
void LCD_PrintHex( const int data );
void LCD_PrintInteger( const int data );

#endif /* LCDDRIVER_H_ */