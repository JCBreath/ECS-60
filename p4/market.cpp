// Author: Sean Davis
#include "market.h"
#include "MarketDriver.h"
#include "QuadraticProbing.h"
#include "AvlTree.h"

Market::Market(int numStocks, int offerCount, int IDs) :
  numStocks(numStocks), offerCount(offerCount), IDs(IDs)
{

} // Market()

void Market::newOffer(const Offer &offer)
{

  lastOffer = offer;
} // newOffer()


bool Market::newTransaction(Transaction *transaction)
{
  Stock *stock;
  Offer *maxOffer, *minOffer;
  int share;

  if(stock = stocks->find(lastOffer->symbol))
  {
    if(lastOffer->type == B && lastOffer->shares > 0 && !stock->sellers->isEmpty()) // buy offer
    {
      minOffer = stock->sellers->findMin(); // min price
      if(minOffer->price <= lastOffer->price) // min price is less than we bid
      {
        transaction->time = 0;
        transaction->buyerID = lastOffer->ID;
        transaction->sellerID = minOffer->ID;
        transaction->price = minOffer->price;
        strcpy(lastOffer->symbol, transaction->symbol);

        if(minOffer->shares >= lastOffer->shares) // enough selling shares
        {
          transaction->shares = lastOffer->shares;
          minOffer->shares -= lastOffer->shares;
          stock->buyers->remove(*lastOffer);
          if(!minOffer->shares)
            stock->sellers->remove(*minOffer);
        }
        else if(minOffer->shares < lastOffer->shares) // not enough
        {
          transaction->shares = minOffer->shares;
          lastOffer->shares -= minOffer->shares;
          stock->sellers->remove(*minOffer);
        }
        return true; // made transaction
      }
    }
    else if(lastOffer->type == S && lastOffer->shares > 0 && !stock->buyers->isEmpty()) // sell offer
    {
      maxOffer = stock->buyers->findMax(); // max price
      if(maxOffer->price >= lastOffer->price) // max price is larger than we sell
      {
        transaction->time = 0;
        transaction->buyerID = maxOffer->ID;
        transaction->sellerID = lastOffer->ID;
        transaction->price = maxOffer->price;
        strcpy(lastOffer->symbol, transaction->symbol);

        if(maxOffer->shares >= lastOffer->shares) // enough buying shares
        {
          transaction->shares = lastOffer->shares;
          maxOffer->shares -= lastOffer->shares;
          stock->sellers->remove(*lastOffer);
          if(!maxOffer->shares)
            stock->buyers->remove(*maxOffer);
        }
        else if(maxOffer->shares < lastOffer->shares) // not enough
        {
          transaction->shares = maxOffer->shares;
          lastOffer->shares -= maxOffer->shares;
          stock->buyers->remove(*maxOffer);
        }
        return true; // made transaction
      }
    }
  }
  
  return false; // means no more transactions, and transaction will be ignored
} // newTransaction()
