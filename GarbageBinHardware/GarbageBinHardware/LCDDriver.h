/*
 * LCDDriver.h
 *
 * Created: 2014-12-22 12:24:29 AM
 *  Author: Justin
 */ 

#ifndef LCDDRIVER_H_
#define LCDDRIVER_H_

#include "Common.h"

void LCD_ClearDisplay();
void LCD_Initialize();
void LCD_PrintHex( const int hexData );
void LCD_PrintInteger( const int intData );
void LCD_PrintMessage( const String msgData );
void LCD_PulseEnableLine();
void LCD_SendByte( const uint8_t byteData );
void LCD_SendChar( const uint8_t charData );
void LCD_SendCommand( const uint8_t cmdData );
void LCD_SendNibble( const uint8_t nibbleData );
void LCD_SetCursorTo( const uint8_t rowIdx, const uint8_t colIdx );
void LCD_SetCursorToHome();
void LCD_SetCursorToLine( const uint8_t rowIdx );

#endif /* LCDDRIVER_H_ */