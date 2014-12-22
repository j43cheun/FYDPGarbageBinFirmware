/*
 * String.h
 *
 * Created: 2014-12-21 10:25:45 PM
 *  Author: Justin
 */ 


#ifndef STRING_H_
#define STRING_H_

#define MAX_BUFFER_SIZE 1000

#include "Common.h"

class String
{
public:
  String();
  String( const char *cstr );
  virtual ~String() {}
private:
  char m_buf[ MAX_BUFFER_SIZE ];
  unsigned m_idx;
};

#endif /* STRING_H_ */