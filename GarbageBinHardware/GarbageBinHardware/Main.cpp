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
#include "TMP36GZDriver.h"
#include "HCSR04Driver.h"

#include <stdio.h>

int main()
{
  // LCD_Init();
  // LCD_PrintMessage( "Hello world" );
  // Wait 2 seconds.
  // _delay_ms( 2000 );

  // Clear the LCD.
  // LCD_ClearDisplay();

  // Wait 2 seconds.
  // _delay_ms( 2000 );

  // Print a message to LCD.
  // LCD_PrintMessage( "State: STANDBY" );

  // Wait 2 seconds.
  // _delay_ms( 2000 );

  // Clear the LCD.
  // LCD_ClearDisplay();

  // Wait 2 seconds.
  // _delay_ms( 2000 );

  // Print a message to LCD.
  // LCD_PrintMessage( "Temp: 30" );

  TMP36GZ_Init();
  HCSR04_Init();

  char buf[100];

  // DDRB = 0xFF;
  // PORTB = 0xFF;

  USART_Init();

  while( 1 )
  {
    float temperature = TMP36GZ_MeasureDegCTemperature();
    float cmDistance = HCSR04_MeasureCmDistance( temperature );
    sprintf(buf, "Temperature: %f Distance: %f cm\n", temperature, cmDistance);
    USART_SendString( buf );
    _delay_ms( 1000 );
  }
  return 0;
}