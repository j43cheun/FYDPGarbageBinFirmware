/*
 * HCSR04Driver.h
 *
 * Created: 2014-12-24 10:09:40 PM
 *  Author: Justin
 */ 

#ifndef HCSR04DRIVER_H_
#define HCSR04DRIVER_H_

#include "Common.h"

ISR( TIMER1_CAPT_vect );
ISR( TIMER1_OVF_vect );

void HCSR04_Enable();
void HCSR04_Disable();
void HCSR04_Init();
float HCSR04_MeasureCmDistance( const float degCTemperature );
float HCSR04_MeasureTransmitToReceiveTime();

#endif /* HCSR04DRIVER_H_ */