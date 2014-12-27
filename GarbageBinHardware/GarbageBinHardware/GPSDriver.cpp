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

TinyGPSPlus GPS_tinyGPS;

GPSCoordinate GPS_GetCoordinate()
{
  struct GPSCoordinate gpsCoordinate;
  bool gpsNotUpdated = true;

  while( gpsNotUpdated )
  {
    const char *recvbuf = USART_ReceiveString( '\n', 5 ).ToCString();
    unsigned recvbufIdx = 0;

    while( recvbuf[ recvbufIdx ] )
    {
      GPS_tinyGPS.encode( recvbuf[ recvbufIdx++ ] );
    }

    if( GPS_tinyGPS.location.isUpdated() || GPS_tinyGPS.altitude.isUpdated() )
    {
      gpsCoordinate.m_latitude = ( float )GPS_tinyGPS.location.lat();
      gpsCoordinate.m_longitude = ( float )GPS_tinyGPS.location.lng();
      gpsNotUpdated = false;
    }
  }

  return gpsCoordinate;
}

void GPS_Init()
{
  USART_Init();
}