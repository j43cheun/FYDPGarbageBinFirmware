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
#include "TinyGPS++.h"
#include "GPSDriver.h"

#include <stdio.h>

int mainold()
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

  TinyGPSPlus gps;

  while( 1 )
  {
    // float temperature = TMP36GZ_MeasureDegCTemperature();
    // float cmDistance = HCSR04_MeasureCmDistance( temperature );
    // sprintf(buf, "Temperature: %f Distance: %f cm\n", temperature, cmDistance);
    // USART_SendString( buf );
    _delay_ms( 1000 );
  }
  return 0;
}

int main()
{
  GPS_Init();

  while( 1 )
  {
    struct GPSCoordinate gpsCoordinate = GPS_GetCoordinate();
    char buf[100];
    sprintf( buf, "LAT: %f LNG: %f\n", gpsCoordinate.m_latitude, gpsCoordinate.m_longitude );
    USART_SendString( buf );
    _delay_ms( 1000 );
  }

  return 0;
}

int mainackers( void )
{
  USART_Init();
  USART_SendString( "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29" );
  USART_SendString( "$PMTK300,10000,0,0,0,0*2C" );
  
  TinyGPSPlus gps;
  
  while( 1 )
  {
    const char* recBuf = USART_ReceiveString( '\n', 5 ).ToCString();
    unsigned idx = 0;
    while( recBuf[idx] )
    {
      gps.encode( recBuf[idx++] );
    }
    
    if (gps.location.isUpdated() || gps.altitude.isUpdated())
    {
      //USART_SendString( "HORRAY!\n" );
      char buf[11];
      sprintf( buf, "%f\n", gps.location.lat() );
      USART_SendString( buf );
      //USART_SendString( recBuf );
    }
    _delay_ms( 1000 );
  }

  return 0;
}