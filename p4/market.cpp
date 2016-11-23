// Author: Sean Davis

#include "market.h"
#include "MarketDriver.h"
#include <cstring>
#include "string.cpp"


Market::Market(int numStocks, int offerCount, int IDs):Table(NULL, 10000)
{
  for(int i=0; i<10000; i++)
  {
    stocks[i].buyers = new BinaryHeap<Offer>;
    stocks[i].sellers = new BinarySearchTree<Offer> (ItemNotFound);
  }
} // Market()


void Market::newOffer(Offer &offer)

{
  lastOffer = offer;
  string sym;
  sym = offer.symbol;
  pos = Table.insert(sym);
} // newOffer()



bool Market::newTransaction(Transaction *transaction)
{
  if (!lastOffer.shares)
    return false;

  if (lastOffer.type == 'B') // buy offer
  {
    Offer *seller = stocks[pos].sellers->findClosest(lastOffer.price);

    if(!seller)
    {
      stocks[pos].buyers->insert(lastOffer);
      return false;
    }
    transaction->time = lastOffer.time;
    transaction->buyerID = lastOffer.ID;
    transaction->sellerID = seller->ID;
    transaction->price = seller->price;
    strcpy(transaction->symbol, lastOffer.symbol);
    if(lastOffer.shares <= seller->shares)
    {
      transaction->shares  = lastOffer.shares;
      lastOffer.shares = 0;
      seller->shares -= transaction->shares;
      if (!seller->shares)
        stocks[pos].sellers->remove(*seller);
      return true;
    }
    else
    {
      transaction->shares  = seller->shares;
      lastOffer.shares -= transaction->shares;
      stocks[pos].sellers->remove(*seller); 
      return true; 
    }
  }
  else // sell offer
  {
    Offer *buyer = stocks[pos].buyers->findMax(); 
    if (!buyer || buyer->price < lastOffer.price){
      stocks[pos].sellers->insert(lastOffer); 
      return false;
    }
    transaction->time = lastOffer.time;
    transaction->buyerID = buyer->ID;
    transaction->sellerID = lastOffer.ID;
    strcpy(transaction->symbol, lastOffer.symbol);
    double price = stocks[pos].buyers->findSecondMax();
    if (lastOffer.price > price)
      transaction->price = lastOffer.price;
    else
      transaction->price = price;
    if (lastOffer.shares <= buyer->shares)
    {   
      transaction->shares  = lastOffer.shares;
      lastOffer.shares = 0;
      buyer->shares -= transaction->shares;
      if (!buyer->shares)
        stocks[pos].buyers->deleteMax();
      return true;
    } 
    else
    { 
      transaction->shares  = buyer->shares;
      lastOffer.shares -= transaction->shares;
      stocks[pos].buyers->deleteMax();
      return true;
    }
  }
  return false;
} // newTransaction()