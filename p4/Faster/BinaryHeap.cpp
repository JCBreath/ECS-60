#include "BinaryHeap.h"
#include "MarketDriver.h"


int BinaryHeap::capacity = 2000;
/**
 * Construct the binary heap.
 * capacity is the capacity of the binary heap.
 */

BinaryHeap::BinaryHeap()
  : currentSize(0)
{
  array = new Offer2[capacity];
}

/**
 * Insert item x into the priority queue, maintaining heap order.
 * Duplicates are allowed.
 * Throw Overflow if container is full.
 */

void BinaryHeap::insert( const Offer & x )
{
        // Percolate up
  int hole = ++currentSize;
  long long priceTime = x.price * 1000;
  priceTime = (priceTime << 32) + 1000000 - x.time;
  
  for( ; hole > 1 && priceTime > array[ hole / 2 ].priceTime; hole /= 2 )
      array[ hole ] = array[ hole / 2 ];
  
  array[ hole ].offer = &x;
  array[hole].priceTime = priceTime;
  array[hole].shares = x.shares;
}

/**
 * Find the smallest item in the priority queue.
 * Return the smallest item, or throw Underflow if empty.
 */

Offer2& BinaryHeap::findMax( )
{
   return array[ 1 ];
}

double BinaryHeap::findSecondPrice()
{
  if(currentSize < 2)
    return 0;
  
  if(currentSize > 2 &&  array[3].offer->price > array[2].offer->price)
    return array[3].offer->price;

  return array[2].offer->price;
}  // findSecondPrice()

void BinaryHeap::deleteMax( )
{
    array[ 1 ] = array[ currentSize-- ];
    percolateDown( 1 );
}



bool BinaryHeap::isEmpty( ) const
{
    return currentSize == 0;
}

/**
 * Test if the priority queue is logically full.
 * Return true if full, false otherwise.
 */

bool BinaryHeap::isFull( ) const
{
    return currentSize == capacity - 1;
}

/**
 * Make the priority queue logically empty.
 */

void BinaryHeap::makeEmpty( )
{
    currentSize = 0;
}

/**
 * Internal method to percolate down in the heap.
 * hole is the index at which the percolate begins.
 */

void BinaryHeap::percolateDown( int hole )
{
  int child;
  Offer2 tmp = array[ hole ];

  for( ; hole * 2 <= currentSize; hole = child )
  {
    child = hole * 2;

    if( child != currentSize 
      && array[ child + 1 ].priceTime > array[ child ].priceTime)
      child++;
    
    if( array[ child ].priceTime > tmp.priceTime )
      array[ hole ] = array[ child ];
    else
       break;
  }

  array[ hole ] = tmp;
}
