// Authors: Sean Davis
#ifndef marketH
#define marketH

#include <cstring>
#include "MarketDriver.h"
#include "QuadraticProbing.h"
#include "AvlTree.h"

class Stock
{
public:
  Stock();
  Offer ItemNotFound;
  AvlTree <Offer> *sellers;
  AvlTree <Offer> *buyers;
  bool isEmpty();
};

class Market
{
public:
  Offer ItemNotFound;
  Market(int numStocks, int offerCount, int IDs); 
  void newOffer(const Offer &offer);
  bool newTransaction(Transaction *transaction);

private:
  Stock stocks[10000];
  QuadraticHashTable <string> Table; 
  int numStocks, offerCount, IDs;
  Offer lastOffer;

}; // class Market

#endif
