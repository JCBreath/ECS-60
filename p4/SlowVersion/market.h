// Authors: Sean Davis
#ifndef marketH
#define marketH

#include "MarketDriver.h"
#include "QuadraticProbing.h"
#include "BinarySearchTree.h"
#include "BinarySearchTree.h"

class Stock
{
public:
  Stock();
  Offer ItemNotFound;
  BinarySearchTree <Offer> *sellers;
  BinarySearchTree <Offer> *buyers;
};

class Market
{
public:
  Offer ItemNotFound;
  Market(int numStocks, int offerCount, int IDs); 
  void newOffer(const Offer &offer);
  bool newTransaction(Transaction *transaction);

private:
  int time = -1;
  Stock stocks[1000000];
  QuadraticHashTable <string> Table; 
  int numStocks, offerCount, IDs;
  Offer lastOffer;

}; // class Market

#endif
