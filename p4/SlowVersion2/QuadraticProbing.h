        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        #include "vector.h"
        #include "mystring.h"

        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings

        template <class HashedObj>
        class QuadraticHashTable
        {
          public:
            explicit QuadraticHashTable( const HashedObj & notFound, int size = 101 );
            QuadraticHashTable( const QuadraticHashTable & rhs )
              : array( rhs.array), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                currentSize( rhs.currentSize ) { }

            int find( const HashedObj & x ) const;

            void makeEmpty( );
            int insert( const HashedObj & x );
            void remove( const HashedObj & x );

            const QuadraticHashTable & operator=( const QuadraticHashTable & rhs );

            enum EntryType { ACTIVE, EMPTY, DELETED };
            int findPos( const HashedObj & x ) const;
          private:
            struct HashEntry
            {
                HashedObj element;
                EntryType info;

                HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
                  : element( e ), info( i ) { }
            };

            HashEntry array[10000];
            int currentSize;
            const HashedObj ITEM_NOT_FOUND;
            bool isPrime( int n ) const;
            int nextPrime( int n ) const;
            bool isActive( int currentPos ) const;
            
            int hash( const string & key, int tableSize ) const;
            int hash( int key, int tableSize ) const;
            void rehash( );
        };

        #include "QuadraticProbing.cpp"
        #endif
