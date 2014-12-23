/*
 * LCDDriver.cpp
 *
 * Created: 10/4/2014 9:39:20 PM
 *  Author: Justin
 */ 

#include "LCDDriver.h"

#define LCD_CTRL_PORT        PORTD
#define LCD_DATA_PORT        PORTC

#define LCD_REGISTER_SELECT  2
#define LCD_ENABLE           3
#define LCD_DATA_4           2
#define LCD_DATA_5           3
#define LCD_DATA_6           4
#define LCD_DATA_7           5

#define LCD_CMD_CLEARDISPLAY 0x01
#define LCD_CMD_SETCURSOR    0x80

void LCD_PulseEnableLine( void )
{
  // Set the LCD ENABLE line to HIGH.
  SetBit( LCD_CTRL_PORT, LCD_ENABLE );

  // Wait 40us.
  _delay_us( 40 );
  
  // Set the LCD ENABLE line to LOW.
  ClearBit( LCD_CTRL_PORT, LCD_ENABLE );
}

void LCD_SendNibble( const byte data )
{
  // (0xC3)16 = (11000011)2 = Clear 4 data lines.
  LCD_DATA_PORT &= 0xC3;
  
  if( data & _BV( 4 ) ) { SetBit( LCD_DATA_PORT, LCD_DATA_4 ); }
  if( data & _BV( 5 ) ) { SetBit( LCD_DATA_PORT, LCD_DATA_5 ); }
  if( data & _BV( 6 ) ) { SetBit( LCD_DATA_PORT, LCD_DATA_6 ); }
  if( data & _BV( 7 ) ) { SetBit( LCD_DATA_PORT, LCD_DATA_7 ); }
  
  // Clock the 4 bits into the controller.
  LCD_PulseEnableLine();
}

void LCD_SendByte( const byte data )
{
  // Set 4 MSB.
  LCD_SendNibble( data );
  
  // Send 4 LSB.
  LCD_SendNibble( data << 4 );  
}

void LCD_SendCmd( const byte cmd )
{
  // Set R/S line to 0 to send command data.
  ClearBit( LCD_CTRL_PORT, LCD_REGISTER_SELECT );
  
  // Send the command data to the LCD.
  LCD_SendByte( cmd );
}

void LCD_SendChar( const byte ch )
{
  // Set R/S line to 1 to send character data.
  SetBit( LCD_CTRL_PORT, LCD_REGISTER_SELECT );
  
  // Send the character data to the LCD.
  LCD_SendByte( ch );
}

void LCD_Init( void )
{
  // Set ports B0 to B5 as outputs.
  DDRC = 0x3C;
  DDRD = 0x0C;
  
  // Initialize the controller.
  LCD_SendCmd( 0x33 );
  
  // Set to 4-bit input mode.
  LCD_SendCmd( 0x32 );

  // 2 line, 5 x 7 matrix.
  LCD_SendCmd( 0x28 );

  // Turn the cursor off. To turn on cursor, set to 0x0E.
  LCD_SendCmd( 0x0C );
  
  // Set the cursor direction to RIGHT.
  LCD_SendCmd( 0x06 );
  
  // Start with a clear display.
  LCD_SendCmd( 0x01 );
  
  // Wait for the LCD to initialize.
  _delay_ms( 3 );
}

void LCD_ClearDisplay( void )
{
  // Send the command to clear the LCD display.
  LCD_SendCmd( LCD_CMD_CLEARDISPLAY );
  
  // Wait for the LCD to process the command.
  _delay_ms( 3 );
}

void LCD_SetCursorToHome( void )
{
  LCD_SendCmd( LCD_CMD_SETCURSOR );
}

void LCD_SetCursorTo( const byte x, const byte y )
{
  byte addr;
  
  switch( y )
  {
    case 1: addr = 0x40; break;
    case 2: addr = 0x14; break;
    case 3: addr = 0x54; break;
    default: addr = 0; break;
  }
  
  LCD_SendCmd( LCD_CMD_SETCURSOR + addr + x );
}

void LCD_SetCursorToLine( const byte row )
{
  LCD_SetCursorTo( 0, row );
}

void LCD_PrintMessage( const char *text )
{
  while( *text ) { LCD_SendChar( *text++ ); }
}

void LCD_PrintHex( const int data )
{
  // Allocate space for result.
  char st[8] = "";
  
  // Convert data to ASCII hex.
  itoa( data, st, 16 );
  
  // Prepend "0x" prefix.
  LCD_PrintMessage( "0x" );
  
  // Print the data to LCD.
  LCD_PrintMessage( st );
}

void LCD_PrintInteger( const int data )
{
  // Allocate space for the result.
  char st[8] = "";
  
  // Convert data to ASCII.
  itoa( data, st, 10 );
  
  // Print the data to LCD.
  LCD_PrintMessage( st );
}