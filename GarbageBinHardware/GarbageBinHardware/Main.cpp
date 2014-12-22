/*
 * Main.cpp
 *
 * Created: 2014-12-21 10:52:35 PM
 *  Author: Justin
 */ 

#include "Common.h"
#include "LCDDriver.h"
#include "String.h"
#include "USARTDriver.h"

int main()
{
  LCD_Initialize();
  String msg( "Hello World!!!" );
  // LCD_PrintMessage( msg );
  LCD_SendChar( 'a' );
  DDRB = 0xFF;
  PORTB = 0xFF;

  USART_Init();

  while( 1 )
  {
    USART_SendString( "Hello. I am your debugger!\n" );
    _delay_ms( 1000 );
  }
  return 0;
}