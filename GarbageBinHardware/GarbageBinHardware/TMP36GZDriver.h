/*
 * TMP36GZDriver.h
 *
 * Created: 2014-12-23 12:58:41 AM
 *  Author: Justin
 */ 

#ifndef TMP36GZDRIVER_H_
#define TMP36GZDRIVER_H_

#include "Common.h"

void TMP36GZ_Init();
uint16_t TMP36GZ_ReadADC();
float TMP36GZ_MeasureDegCTemperature();

#endif /* TMP36GZDRIVER_H_ */