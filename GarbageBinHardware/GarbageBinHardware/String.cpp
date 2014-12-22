/*
 * String.cpp
 *
 * Created: 2014-12-21 10:26:11 PM
 *  Author: Justin
 */ 

#include "String.h"

String::String() : m_idx( 0 )
{
  m_buf[ m_idx ] = '\0';
}

String::String( const char *cstr ) : m_idx( 0 )
{
  unsigned idxLimit = MAX_BUFFER_SIZE - 1;

  while( cstr[ m_idx ] && m_idx < idxLimit )
  {
    m_buf[ m_idx ] = cstr[ m_idx ];
    m_idx++;
  }

  m_buf[ m_idx ] = '\0';
}

void *operator new( size_t sizeInBytes )
{
  void *const buf = malloc( sizeInBytes );
  return buf;
}

void operator delete( void *buf )
{
  free( buf );
}