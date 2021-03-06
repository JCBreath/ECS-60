// Authors: Sean Davis
#ifndef marketH
#define marketH

#include "MarketDriver.h"
#include "BinaryHeap.h"
#include "QuadraticProbing.h"
#include "BinarySearchTree.h"


class Market
{
  BinaryHeap *buyingHeaps;
  BinarySearchTree *sellingTrees;
  int counts[3792];
  QuadraticHashTable symbolTable;
  int stockIndex;
  int time;
public:
  Market(int numStocks, int offerCount, int IDs);
  void newOffer(const Offer &offer);
  bool newTransaction(Transaction *transaction);
}; // class Market

#endif
