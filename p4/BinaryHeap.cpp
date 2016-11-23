        #include "BinaryHeap.h"

        /**
         * Construct the binary heap.
         * capacity is the capacity of the binary heap.
         */
        template <class Comparable>
        BinaryHeap<Comparable>::BinaryHeap( int capacity )
          : currentSize(0), array( capacity + 1 )
        {
        }

        /**
         * Insert item x into the priority queue, maintaining heap order.
         * Duplicates are allowed.
         * Throw Overflow if container is full.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::insert( const Comparable & x )
        {
            int hole = ++currentSize;
            for( ; hole > 1 && ((x.price > array[ hole / 2 ].price) || (x.price == array[ hole / 2 ].price && x.time < array[ hole / 2 ].time)); hole /= 2 )
                array[ hole ] = array[ hole / 2 ];
            array[ hole ] = x;
        }

        /**
         * Find the smallest item in the priority queue.
         * Return the smallest item, or throw Underflow if empty.
         */
        template <class Comparable>
        Comparable * BinaryHeap<Comparable>::findMax( )
        {
            if(isEmpty())
                return NULL;
            return &array[ 1 ];
        }

        template <class Comparable>
        double BinaryHeap<Comparable>::findSecondMax()
        {
            if (currentSize >= 3) 
            {
               if (array[2].price >= array[3].price)
                  return  array[2].price;
               return array[3].price;
            }

            else if (currentSize == 2)
                return array[2].price;
            else
                return 0; // not found
       }

        /**
         * Remove the smallest item from the priority queue.
         * Throw Underflow if empty.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::deleteMax( )
        {
            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
        }

        /**
         * Remove the smallest item from the priority queue
         * and place it in MaxItem. Throw Underflow if empty.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::deleteMax( Comparable & MaxItem )
        {
            MaxItem = array[ 1 ];
            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
        }

        /**
         * Establish heap order property from an arbitrary
         * arrangement of items. Runs in linear time.
         */


        /**
         * Test if the priority queue is logically empty.
         * Return true if empty, false otherwise.
         */

        template <class Comparable>
        bool BinaryHeap<Comparable>::isEmpty( ) const
        {
            return currentSize == 0;
        }

        /**
         * Test if the priority queue is logically full.
         * Return true if full, false otherwise.
         */
        template <class Comparable>
        bool BinaryHeap<Comparable>::isFull( ) const
        {
            return currentSize == array.size( ) - 1;
        }

        /**
         * Make the priority queue logically empty.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::makeEmpty( )
        {
            currentSize = 0;
        }

        /**
         * Internal method to percolate down in the heap.
         * hole is the index at which the percolate begins.
         */
        template <class Comparable>
        void BinaryHeap<Comparable>::percolateDown( int hole )
        {
/* 1*/      int child;
/* 2*/      Comparable tmp = array[ hole ];
/* 3*/      for( ; hole * 2 <= currentSize; hole = child )
            {
/* 4*/          child = hole * 2;
/* 5*/          if( child != currentSize && (array[ child + 1 ].price > array[ child ].price  || (array[ child + 1 ].price == array[ child ].price && array[ child + 1 ].time < array[ child ].time)))
/* 6*/              child++;
/* 7*/          if( array[ child ].price > tmp.price || (array[ child ].price == tmp.price && array[ child ].time < tmp.time) )
/* 8*/              array[ hole ] = array[ child ];
                else
/* 9*/              break;
            }
/*10*/      array[ hole ] = tmp;
        }
