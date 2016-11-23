// Authors: Sean Davis
#ifndef marketH
#define marketH

#include "MarketDriver.h"
#include "QuadraticProbing.h"
#include "BinarySearchTree.h"
#include "BinaryHeap.h"

class Stock
{
public:
  Offer ItemNotFound;
  BinarySearchTree <Offer> *sellers;
  BinaryHeap <Offer> *buyers;
};

class Market
{
public:
  Offer ItemNotFound;
  Market(int numStocks, int offerCount, int IDs); 
  void newOffer(Offer &offer);
  bool newTransaction(Transaction *transaction);

private:
  int pos = -1;
  Stock stocks[10000];
  QuadraticHashTable <string> Table; 
  int numStocks, offerCount, IDs;
  Offer lastOffer;

}; // class Market

#endif
