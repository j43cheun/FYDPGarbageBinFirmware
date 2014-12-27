/*
 * USARTDriver.cpp
 *
 * Created: 2014-12-22 4:18:26 PM
 *  Author: Justin
 */ 

#include "USARTDriver.h"

#include "Common.h"
#include "String.h"

#define BAUDRATE       9600
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)

volatile bool USART_initializeFlag = false;

void USART_Init( void )
{
  if( !USART_initializeFlag )
  {
    UBRR0H = ( BAUD_PRESCALER >> 8 );
    UBRR0L = ( BAUD_PRESCALER );
    UCSR0B |= ( 1 << RXEN0 ) | ( 1 << TXEN0 );
    UCSR0C |= ( 1 << UCSZ00 ) | ( 1 << UCSZ01 );
    USART_initializeFlag = true;
  }
}

bool USART_ByteAvailable()
{
  return ( UCSR0A & ( 1 << UDRE0 ) );
}

unsigned char USART_ReadByte()
{
  return UDR0;
}

unsigned char USART_ReceiveByte( void )
{
  while( !( UCSR0A & ( 1 << RXC0 ) ) );
  return UDR0;
}

String USART_ReceiveString( unsigned char terminator, unsigned terminationCount )
{
  String receivedString;
  unsigned char receivedByte;
  unsigned newlineCount = 0;
  
  do
  {
    while( !( UCSR0A & ( 1 << RXC0 ) ) );
    receivedByte = UDR0;
    receivedString += receivedByte;
    
    if( receivedByte == terminator )
    {
      newlineCount++;
    }
    
  } while( !receivedString.BufferIsFull() && newlineCount < terminationCount );

  return receivedString;
}

void USART_SendByte( unsigned char data )
{
  while( ! ( UCSR0A & ( 1 << UDRE0 ) ) );
  UDR0 = data;
}

void USART_SendString( const char* stringPtr )
{
  while( *stringPtr != 0x00 )
  {
    USART_SendByte( *stringPtr++ );
  }
}