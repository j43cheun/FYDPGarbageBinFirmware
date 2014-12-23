/*
 * TMP36GZDriver.cpp
 *
 * Created: 2014-12-23 1:10:02 AM
 *  Author: Justin
 */ 

#include "TMP36GZDriver.h"

#define TMP36GZ_CHANNEL 1

void TMP36GZ_Init()
{
  // Set the ADC prescaler to 128 (i.e., 16MHz / 128 = 125 KHz).
  ADCSRA |= ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 1 << ADPS0 );

  // Set the voltage reference from AVcc (i.e., 5V).
  ADMUX |= ( 1 << REFS0 );

  // Turn on the ADC.
  ADCSRA |= ( 1 << ADEN );

  // Do the initial conversion (i.e., the slowest conversion)
  // to ensure that everything is up and running.
  ADCSRA |= ( 1 << ADSC );
}

uint16_t TMP36GZ_ReadADC()
{
  // Clear the previously read channel.
  ADMUX &= 0xf0;
  
  // Select the ADC channel to be read.
  ADMUX |= TMP36GZ_CHANNEL;
  
  // Start a new conversion. By default, this conversion will
  // be performed in single conversion mode.
  ADCSRA |= ( 1 << ADSC );
  
  // Wait until the conversion is complete.
  // while( ADCSRA & ( 1 << ADSC ) );
  while( ADCSRA & ( 1 << ADIF ) );

  // Obtain the ADC reading from Vout.
  uint16_t adcReading = ADC;

  // Clear the ADIF flag.
  ADCSRA |= ( 1 << ADIF );

  // Return the ADC reading.
  return adcReading;
}

float TMP36GZ_MeasureDegCTemperature()
{
  // Get ADC reading from TMP36GZ.
  uint16_t adcReading = TMP36GZ_ReadADC();
  
  // Compute analog voltage in mV from ADC reading. Assume 5V reference.
  float mvVoltage = ( float )adcReading * ( 5000.0 / 1024.0 );
  
  // Compute the temperature in degrees Celsius.
  float degCTemperature = ( mvVoltage - 500.0 ) / 10.0;

  // Return the temperature.
  return degCTemperature;
}