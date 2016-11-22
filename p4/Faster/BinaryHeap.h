#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include "MarketDriver.h"

class Offer2
{
public:
  const Offer *offer;
  long long priceTime;
  int shares;
  Offer2(){}
  Offer2(const Offer *off) : offer(off), shares(off->shares)
  {
    priceTime = off->price * 1000;
    priceTime = (priceTime << 32) + 1000000 - off->time;
  }
};  // class Offer2

class BinaryHeap
{
  public:
    explicit BinaryHeap();
    bool isEmpty( ) const;
    bool isFull( ) const;
    Offer2&  findMax( );
    double findSecondPrice();

    void insert(const Offer & x );
    void deleteMax( );
    void makeEmpty( );

    int    currentSize;  // Number of elements in heap
    static int capacity;
    Offer2 *array;        // The heap array
    void percolateDown( int hole );
};

#endif
