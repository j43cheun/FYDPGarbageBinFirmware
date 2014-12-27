/*
 * GPSDriver.h
 *
 * Created: 2014-12-27 1:57:32 AM
 *  Author: Justin
 */ 

#ifndef GPSDRIVER_H_
#define GPSDRIVER_H_

#include "Common.h"

struct GPSCoordinate
{
  float m_latitude;
  float m_longitude;
};

GPSCoordinate GPS_GetCoordinate();
void GPS_Init();

#endif /* GPSDRIVER_H_ */