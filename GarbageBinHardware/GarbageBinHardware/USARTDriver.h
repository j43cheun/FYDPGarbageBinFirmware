/*
 * USARTDriver.h
 *
 * Created: 2014-12-22 4:17:11 PM
 *  Author: Justin
 */ 


#ifndef USARTDRIVER_H_
#define USARTDRIVER_H_

class String;

void USART_Init( void );
bool USART_ByteAvailable();
unsigned char USART_ReadByte( void );
unsigned char USART_ReceiveByte( void );
String USART_ReceiveString( unsigned char terminator, unsigned terminationCount );
void USART_SendByte( unsigned char data );
void USART_SendString( char* stringPtr );

#endif /* USARTDRIVER_H_ */