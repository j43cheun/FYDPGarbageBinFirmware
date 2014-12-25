/*
 * HCSR04Driver.cpp
 *
 * Created: 2014-12-24 10:15:37 PM
 *  Author: Justin
 */ 

#include "HCSR04Driver.h"
#include "USARTDriver.h"
#include <stdio.h>

#define HCSR04_ECHO    0        // PB0
#define HCSR04_TRIG    1        // PB1

volatile uint16_t HCSR04_measuredTransmitToReceiveTime = 0;
volatile bool HCSR04_timerOverflowFlag = false;
volatile bool HCSR04_waitFlag = false;

ISR( TIMER1_OVF_vect )
{
  // Indicate that TIMER1 counter has overflowed.
  HCSR04_timerOverflowFlag = true;

  // Indicate that the program can stop waiting.
  HCSR04_waitFlag = false;
}

ISR( TIMER1_CAPT_vect )
{
  // If input capture was previously on a rising edge trigger...
  if( ( TCCR1B & ( 1 << ICES1 ) ) == ( 1 << ICES1 ) )
  {
    // Reset input capture to a falling edge trigger.
    TCCR1B ^= ( 1 << ICES1 );

    // Restart TIMER1 counter counting from 0.
    TCNT1 = 0;
  }
  else
  {
    // Set the transmit to receive time.
    HCSR04_measuredTransmitToReceiveTime = TCNT1;

    // Indicate that the program can stop waiting.
    HCSR04_waitFlag = false;
  }
}

void HCSR04_Enable()
{
  // Disable all interrupts on the ATMEGA328p.
  cli();

  // Clear the timer/counter control registers for TIMER1.
  // Setting TCCR1C to 0x00 sets TIMER1 to NORMAL MODE.
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR1C = 0x00;

  // Enable rising edge trigger with prescaler of 8.
  TCCR1B |= ( 1 << CS11 ) | ( 1 << ICES1 );

  // Enable input capture and overflow interrupts.
  TIMSK1 |= ( 1 << ICIE1 ) | ( 1 << TOIE1 );

  // Start TIMER1 counter counting from 0.
  TCNT1 = 0;

  // Re-enable all interrupts.
  sei();
}

void HCSR04_Disable()
{
  // Disable input capture and overflow interrupts on TIMER1.
  TIMSK1 = 0x00;

  // Stop timer.
  TCCR1B = 0x00;
}

void HCSR04_Init()
{
  // Set PB0 (ECHO) as INPUT and PB1 (TRIG) as OUTPUT.
  DDRB |= ( 1 << HCSR04_TRIG );
}

float HCSR04_MeasureCmDistance( const float degCTemperature )
{
  // Measure the transmit to receive time in half microseconds (us).
  // Note that the period between two consecutive ticks is 1 / ( 16MHz / 8 ) = 0.5us.
  // 16MHz is the clock rate of the ATMEGA328p and 8 is the prescaler.
  float transmitToReceiveTime = HCSR04_MeasureTransmitToReceiveTime();

  // Distance in cm.
  float cmDistance;

  // If TIMER1 has overflowed...
  if( HCSR04_timerOverflowFlag )
  {
    cmDistance = -1;
  }
  else
  {
    // Calculate the approximate time duration in microseconds from the HCSR04 to the target.
    // We divide transmit to receive time by 2 to get the start to target duration in half 
    // microseconds. We further divide this value by 2 to get the start to target duration in
    // microseconds. This is equivalent to dividing transmit to receive time by 4.
    float startToTargetDuration = transmitToReceiveTime / 4.0;
    
    // Calculate the approximate speed of sound given the temperature in degrees Celsius.
    float speedOfSound = 331.0 + ( 0.6 * degCTemperature );
    
    // Calculate the distance in cm. If we don't divide by 10000, we get the distance in m.
    cmDistance = ( speedOfSound * startToTargetDuration ) / 10000.0;
  }

  // Return the distance.
  return cmDistance;
}

float HCSR04_MeasureTransmitToReceiveTime()
{
  // Reset timer overflow flag to false.
  HCSR04_timerOverflowFlag = false;

  // Set TRIG to LOW for approximately 2us.
  ClearBit( PORTB, HCSR04_TRIG );
  _delay_us( 2 );

  // Set TRIG to HIGH for approximately 10us.
  SetBit( PORTB, HCSR04_TRIG );
  _delay_us( 10 );

  // Set TRIG to LOW after 10us HIGH pulse.
  ClearBit( PORTB, HCSR04_TRIG );

  // Enable timer overflow and input capture interrupts on ECHO.
  HCSR04_Enable();

  // Set the WAIT flag to TRUE.
  HCSR04_waitFlag = true;

  // Wait until the WAIT flag becomes false.
  while( HCSR04_waitFlag );

  // Disable the input capture and overflow interrupts on TIMER1.
  HCSR04_Disable();

  // Transmit to receive time.
  float transmitToReceiveTime;

  // Check if TIMER1 has overflowed...
  if( HCSR04_timerOverflowFlag )
  {
    // Set transmit to receive time to -1 to indicate that TIMER1 has overflowed.
    transmitToReceiveTime = -1;
  }
  else
  {
    // Set transmit to receive time to measured transmit to receive time.
    transmitToReceiveTime = ( float )HCSR04_measuredTransmitToReceiveTime;
  }

  // Return the transmit to receive time.
  return transmitToReceiveTime;
}