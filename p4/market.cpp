// Author: Sean Davis

#include "market.h"
#include "string.cpp"

Stock::Stock()
{
  ItemNotFound.price = 0;
  buyers = new AvlTree<Offer> (ItemNotFound);
  sellers = new AvlTree<Offer> (ItemNotFound);
}

bool Stock::isEmpty()
{
/*  if(sellers.isEmpty() && buyers.isEmpty())
    return true;
  else
    return false;*/
}

Market::Market(int numStocks, int offerCount, int IDs) :
  numStocks(numStocks), offerCount(offerCount), IDs(IDs), Table(NULL, 10000)
{
} // Market()

void Market::newOffer(const Offer &offer)
{
  string sym;
  sym = offer.symbol;
  int pos = Table.findPos(sym);

  if(pos != NULL)
  {
    if(offer.type == 'B') // buy offer
        stocks[pos].buyers->insert(offer);
    else // sell offer
        stocks[pos].sellers->insert(offer);
  }
  else
  {
    Table.insert(sym);
    ItemNotFound.price = 0;
    stocks[pos].buyers = new AvlTree<Offer> (ItemNotFound);
    stocks[pos].sellers = new AvlTree<Offer> (ItemNotFound);
    newOffer(offer);
  }
  cout<<"B-"<<sym<<endl;
  stocks[pos].buyers->printTree();
  cout<<"S-"<<sym<<endl;
  stocks[pos].sellers->printTree();
  lastOffer = offer;
} // newOffer()


bool Market::newTransaction(Transaction *transaction)
{
  Stock *stock = stocks + Table.findPos(lastOffer.symbol);
  Offer *maxOffer, *minOffer, min, max;
  int share;
  
  if(stock && lastOffer.shares > 0)
  {
    if(lastOffer.type == 'B' && !stock->sellers->isEmpty()) // buy offer
    {

      minOffer = stock->sellers->findMin(); // min price

      min = *minOffer;
      if(minOffer->price <= lastOffer.price) // min price is less than we bid
      {
        
        transaction->time = 0;
        transaction->buyerID = lastOffer.ID;
        transaction->sellerID = minOffer->ID;
        transaction->price = minOffer->price;
        strcpy(transaction->symbol, lastOffer.symbol);

        if(minOffer->shares >= lastOffer.shares) // enough selling shares
        {
          transaction->shares = lastOffer.shares;
          minOffer->shares -= lastOffer.shares;
          stock->buyers->remove(lastOffer);
          lastOffer.shares = 0;
          if(!minOffer->shares)
            stock->sellers->remove(min);
        }

        else if(minOffer->shares < lastOffer.shares) // not enough
        {
          
          transaction->shares = minOffer->shares;
          lastOffer.shares -= minOffer->shares;
          stock->sellers->remove(min);
        }

        return true; // made transaction
      }
    }
    else if(lastOffer.type == 'S' && !stock->buyers->isEmpty()) // sell offer
    {
      cout<<"SHARES"<<lastOffer.shares<<endl;
      maxOffer = stock->buyers->findMax(); // max price
      cout<<"MAX"<<maxOffer->shares<<endl;
      max = *maxOffer;
      if(maxOffer->price >= lastOffer.price) // max price is larger than we sell
      {
        transaction->time = 0;
        transaction->buyerID = maxOffer->ID;
        transaction->sellerID = lastOffer.ID;
        transaction->price = maxOffer->price;
        strcpy(transaction->symbol, lastOffer.symbol);

        if(maxOffer->shares >= lastOffer.shares) // enough buying shares
        {
          transaction->shares = lastOffer.shares;
          maxOffer->shares -= lastOffer.shares;
          stock->sellers->remove(lastOffer);
          lastOffer.shares = 0;
          if(maxOffer->shares == 0)
            stock->buyers->remove(max);
        }
        else if(maxOffer->shares < lastOffer.shares) // not enough
        {
          transaction->shares = maxOffer->shares;
          lastOffer.shares -= maxOffer->shares;
          stock->buyers->remove(max);
        }
              cout<<"SHARES-AFTER"<<lastOffer.shares<<endl;
      cout<<"MAX-AFTER"<<maxOffer->shares<<endl;
        return true; // made transaction
      }
    }
  }
  return false; // means no more transactions, and transaction will be ignored
} // newTransaction()
