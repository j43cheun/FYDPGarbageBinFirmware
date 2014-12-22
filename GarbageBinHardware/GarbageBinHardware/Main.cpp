/*
 * Main.cpp
 *
 * Created: 2014-12-21 10:52:35 PM
 *  Author: Justin
 */ 

#include "Common.h"
#include "LCDDriver.h"

int main()
{
  //LCD_Initialize();
  //String msg( "Hello World!!!" );
  //LCD_PrintMessage( msg );
  DDRC = 0xFF;
  while( 1 );
  return 0;
}