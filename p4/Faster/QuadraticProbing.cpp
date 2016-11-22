#include <cstring>
#include "QuadraticProbing.h"



int QuadraticHashTable::find(const char symbol[]) 
{
  int currentPos = 0;
 
  for( int i = 0; symbol[i]; i++ )
    currentPos = 37 * currentPos + symbol[ i ];

  currentPos %= size;
  
  if( currentPos < 0 )
    currentPos += size;

  while(array[currentPos].symbol[0] && strcmp(array[currentPos].symbol, symbol) != 0)
    currentPos = ++currentPos % size;

  if(array[currentPos].symbol[0] == 0)
  {
    strcpy (array[currentPos].symbol, symbol);
    array[currentPos].index = count++;
  }

  return array[currentPos].index;
}
