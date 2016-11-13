// Authors: Sean Davis
#ifndef marketH
#define marketH

#include "MarketDriver.h"
#include "QuadraticProbing.h"
#include "AvlTree.h"

class Market
{
public:
  Market(int numStocks, int offerCount, int IDs);
  void newOffer(const Offer &offer);
  bool newTransaction(Transaction *transaction);

private:
  int numStocks, offerCount, IDs;
  Offer *lastOffer;

}; // class Market

#endif
