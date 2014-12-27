/*
 * GPSDriver.cpp
 *
 * Created: 2014-12-27 2:02:30 AM
 *  Author: Justin
 */ 

#include "GPSDriver.h"
#include "String.h"
#include "TinyGPS++.h"
#include "USARTDriver.h"

volatile bool GPS_timeoutFlag = false;
TinyGPSPlus GPS_tinyGPS;

GPSCoordinate GPS_GetCoordinate()
{
  struct GPSCoordinate gpsCoordinate;
  bool gpsNotUpdated = true;

  // While GPS has not yet been updated and timeout has not occurred yet...
  while( gpsNotUpdated && !GPS_timeoutFlag )
  {
    // Encode bytes received from GPS hardware.
    const char *recvbuf = USART_ReceiveString( '\n', 5 ).ToCString();
    unsigned recvbufIdx = 0;

    while( recvbuf[ recvbufIdx ] )
    {
      GPS_tinyGPS.encode( recvbuf[ recvbufIdx++ ] );
    }

    // If GPS info is updated, update return structure with updated latitude 
    // and longitude, and a valid flag set to true.
    if( GPS_tinyGPS.location.isUpdated() || GPS_tinyGPS.altitude.isUpdated() )
    {
      gpsCoordinate.m_latitude = ( float )GPS_tinyGPS.location.lat();
      gpsCoordinate.m_longitude = ( float )GPS_tinyGPS.location.lng();
      gpsCoordinate.m_valid = true;
      gpsNotUpdated = false;
    }
  }

  // Check if a timeout has occurred. If so, set valid flag in return 
  // structure to false.
  if( GPS_timeoutFlag )
  {
    gpsCoordinate.m_valid = false;
    GPS_timeoutFlag = false;
  }

  // Return GPSCoordinate structure.
  return gpsCoordinate;
}

void GPS_Init()
{
  // Initialize the USART driver if not already initialized.
  USART_Init();

  // TODO Implement with timeout to break out of potentially infinite loop.
  // Use one of the available timers to timeout the operation.
}