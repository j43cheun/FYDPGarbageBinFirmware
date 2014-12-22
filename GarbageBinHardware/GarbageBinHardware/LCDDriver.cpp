/*
 * LCDDriver.cpp
 *
 * Created: 2014-12-22 12:30:15 AM
 *  Author: Justin
 */ 

#include "LCDDriver.h"
#include "String.h"

// ATMEGA328P PDx PORTS
#define REGISTER_SELECT_PIN               2
#define ENABLE_PIN                        3

// ATMEGA328P PCx PORTS
#define DATA_4_PIN                        2
#define DATA_5_PIN                        3
#define DATA_6_PIN                        4
#define DATA_7_PIN                        5

// LCD COMMANDS
#define CMD_CLEAR_DISPLAY                 0x01
#define CMD_INIT_CONTROLLER               0x33
#define CMD_SET_2_LINE_5X7_MATRIX         0x28
#define CMD_SET_4_BIT_MODE                0x32
#define CMD_SET_CURSOR                    0x80
#define CMD_SET_CURSOR_DIRECTION_TO_RIGHT 0x06
#define CMD_TURN_OFF_CURSOR               0x0C
#define CMD_TURN_ON_CURSOR                0x0E

void LCD_ClearDisplay()
{
  // Send the command to clear the LCD display.
  LCD_SendCommand( CMD_CLEAR_DISPLAY );

  // Wait for the LCD to process the command.
  _delay_ms( 3 );
}

void LCD_Initialize()
{
  // Set ports PD2 and PD3 as outputs.
  DDRD |= ( 1 << REGISTER_SELECT_PIN ) |
          ( 1 << ENABLE_PIN );

  // Set ports PC4 to PC7 as outputs.
  DDRC |= ( 1 << DATA_4_PIN ) |
          ( 1 << DATA_5_PIN ) |
          ( 1 << DATA_6_PIN ) |
          ( 1 << DATA_7_PIN );

  // Initialize the controller.
  LCD_SendCommand( CMD_INIT_CONTROLLER );

  // Set to 4-bit input mode.
  LCD_SendCommand( CMD_SET_4_BIT_MODE );

  // 2 line, 5 x 7 matrix.
  LCD_SendCommand( CMD_SET_2_LINE_5X7_MATRIX );

  // Turn the cursor off.
  LCD_SendCommand( CMD_TURN_OFF_CURSOR );

  // Set the cursor direction to RIGHT.
  LCD_SendCommand( CMD_SET_CURSOR_DIRECTION_TO_RIGHT );

  // Start with a clear display.
  LCD_SendCommand( CMD_CLEAR_DISPLAY );

  // Wait for the LCD to initialize.
  _delay_ms( 3 );
}

void LCD_PrintHex( const int hexData )
{
  // Allocate space for result.
  char hexDataCStrBuf[ 8 ];

  // Convert hex data to ASCII.
  itoa( hexData, hexDataCStrBuf, 16 );

  // Print "0x" prefix.
  String hexPrefix( "0x" );
  LCD_PrintMessage( hexPrefix );

  // Print the hex data to LCD.
  String hexDataStr( hexDataCStrBuf );
  LCD_PrintMessage( hexDataStr );
}

void LCD_PrintInteger( const int intData )
{
  // Allocate space for result.
  char intDataCStrBuf[ 8 ];

  // Convert int data to ASCII.
  itoa( intData, intDataCStrBuf, 10 );

  // Print the int data to LCD.
  LCD_PrintMessage( intDataCStrBuf );
}

void LCD_PrintMessage( const String msgData )
{
  // const char *cstr = msgData.ToCString();
  char *cstr = "hello world!";
  while( *cstr ) { LCD_SendChar( *cstr++ ); }
}

void LCD_PulseEnableLine()
{
  // Set the LCD ENABLE line to HIGH.
  PORTD |= ( 1 << ENABLE_PIN );

  // Wait 40us.
  _delay_us( 40 );

  // Set the LCD ENABLE line to LOW.
  PORTD &= ~( 1 << ENABLE_PIN );
}

void LCD_SendByte( const uint8_t byteData )
{
  // Set 4 MSB.
  LCD_SendNibble( byteData );

  // Set 4 LSB.
  LCD_SendNibble( byteData << 4 );
}

void LCD_SendChar( const uint8_t charData )
{
  // Set LCD REGISTER SELECT line to 1 to send char data.
  PORTD |= ( 1 << REGISTER_SELECT_PIN );

  // Send the char data to the LCD.
  LCD_SendByte( charData );
}

void LCD_SendCommand( const uint8_t cmdData )
{
  // Set LCD REGISTER SELECT line to 0 to send command data.
  PORTD &= ~( 1 << REGISTER_SELECT_PIN );

  // Send the command data to the LCD.
  LCD_SendByte( cmdData );
}

void LCD_SendNibble( const uint8_t nibbleData )
{
  // Clear DATA lines.
  PORTC &= ~( ( 1 << DATA_4_PIN ) |
              ( 1 << DATA_5_PIN ) |
              ( 1 << DATA_6_PIN ) |
              ( 1 << DATA_7_PIN ) );
  
  if( nibbleData & ( 1 << 4 ) ) { PORTC |= ( 1 << DATA_4_PIN ); }
  if( nibbleData & ( 1 << 5 ) ) { PORTC |= ( 1 << DATA_5_PIN ); }
  if( nibbleData & ( 1 << 6 ) ) { PORTC |= ( 1 << DATA_6_PIN ); }
  if( nibbleData & ( 1 << 7 ) ) { PORTC |= ( 1 << DATA_7_PIN ); }

  // Clock the 4 bits into the controller.
  LCD_PulseEnableLine();
}

void LCD_SetCursorTo( const uint8_t rowIdx, const uint8_t colIdx )
{
  uint8_t addr;

  switch( colIdx )
  {
    case 1: addr = 0x40; break;
    case 2: addr = 0x14; break;
    case 3: addr = 0x54; break;
    default: addr = 0; break;
  }

  LCD_SendCommand( CMD_SET_CURSOR + addr + rowIdx );
}

void LCD_SetCursorToHome()
{
  LCD_SendCommand( CMD_SET_CURSOR );
}

void LCD_SetCursorToLine( const uint8_t rowIdx )
{
  LCD_SetCursorTo( 0, rowIdx );
}