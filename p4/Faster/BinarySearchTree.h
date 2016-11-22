 #ifndef _BINARY_SEARCH_TREE_H_
 #define _BINARY_SEARCH_TREE_H_

 #include <iostream>// For NULL
#include "BinaryHeap.h"

 // Binary node and forward declaration because g++ does
 // not understand nested classes.
 class BinaryNode
 {
   Offer2 element;
   BinaryNode *left;
   BinaryNode *right;

   BinaryNode(const Offer2 & theElement, BinaryNode *lt, BinaryNode *rt )
     : element( theElement ), left( lt ), right( rt ) { }
   friend class BinarySearchTree;
 };


 class BinarySearchTree
 {
 public:
   BinarySearchTree( );
   Offer2* find(double price);
   void printTree( ) const;
   void insert(const Offer & x );
   void remove(long long priceTime);
 private:
   BinaryNode *root;
   BinaryNode **prev;
   void printTree( BinaryNode *t ) const;
 };

 #endif
