// Author: Sean Davis
#include "dsexceptions.h"
#include "market.h"
#include "string.cpp"

Stock::Stock()
{
  ItemNotFound.price = 0;
  buyers = new BinarySearchTree<Offer> (ItemNotFound);
  sellers = new BinarySearchTree<Offer> (ItemNotFound);
}

Market::Market(int numStocks, int offerCount, int IDs) :
  numStocks(numStocks), offerCount(offerCount), IDs(IDs), Table(NULL, 1000000)
{
} // Market()

void Market::newOffer(const Offer &offer)
{
  string sym;
  sym = offer.symbol;
  int pos = Table.findPos(sym);
  if(Table.find(sym) != NULL)
  {
    if(offer.type == 'B') // buy offer
    {
      stocks[pos].buyers->insert(offer);
    }
    else // sell offer
    {
      stocks[pos].sellers->insert(offer);
    }
  }
  else
  {
    Table.insert(sym);
    ItemNotFound.price = 0;
    stocks[pos].buyers = new BinarySearchTree<Offer> (ItemNotFound);
    stocks[pos].sellers = new BinarySearchTree<Offer> (ItemNotFound);
    newOffer(offer);
  }
  lastOffer = offer;
} // newOffer()


bool Market::newTransaction(Transaction *transaction)
{
  Stock *stock = stocks + Table.findPos(lastOffer.symbol);
  Offer *maxOffer, *closestOffer, closest, max;
  int share;
  //cout<<lastOffer.time<<endl;
  if(stock && lastOffer.shares > 0)
  {
    if(lastOffer.type == 'B' && !stock->sellers->isEmpty()) // buy offer
    {
      double transPrice;
      BinarySearchTree <Offer> temp = *stock->sellers;

      while(!temp.isEmpty())
      {
        max = *temp.findMax();
        if(max.price <= lastOffer.price)
        {
          closestOffer = stock->sellers->find(max);
          //cout<<closestOffer->price;
          break;
        }
        else
          temp.remove(max);
      }

      if(temp.isEmpty())
        return false;
      
      closest = *closestOffer;

      temp = *stock->buyers;
      if(!temp.isEmpty())
      {
        temp.remove(*temp.findMax());
        if(!temp.isEmpty())
        {
          transPrice = temp.findMax()->price;
          if(transPrice < closestOffer->price)
            transPrice = closestOffer->price;
        }
        else
          transPrice = closestOffer->price;
      }
      else
        transPrice = closestOffer->price;

      if(closestOffer->price <= lastOffer.price) // closest price is less than we bid
      {
        
        transaction->time = lastOffer.time;
        transaction->buyerID = lastOffer.ID;
        transaction->sellerID = closestOffer->ID;
        transaction->price = transPrice;
        strcpy(transaction->symbol, lastOffer.symbol);

        if(closestOffer->shares >= lastOffer.shares) // enough selling shares
        {
          transaction->shares = lastOffer.shares;
          closestOffer->shares -= lastOffer.shares;
          stock->buyers->remove(lastOffer);
          lastOffer.shares = 0;
          if(!closestOffer->shares)
            stock->sellers->remove(closest);
        }

        else if(closestOffer->shares < lastOffer.shares) // not enough
        {
          
          transaction->shares = closestOffer->shares;
          lastOffer.shares -= closestOffer->shares;
          stock->sellers->remove(closest);
          stock->buyers->find(lastOffer)->shares = lastOffer.shares;
        }
        return true; // made transaction
      }
    }
    else if(lastOffer.type == 'S' && !stock->buyers->isEmpty()) // sell offer
    {
      double transPrice;
      maxOffer = stock->buyers->findMax(); // max price
      max = *maxOffer;

      BinarySearchTree <Offer> temp = *stock->buyers;
      if(!temp.isEmpty())
      {
        temp.remove(max);
        if(!temp.isEmpty()) // if second highest bidder exists
        {
          transPrice = temp.findMax()->price; // second highest bidder
          if(transPrice < lastOffer.price)
          transPrice = lastOffer.price;
        }
        else
          transPrice = lastOffer.price;
      }
      else
        transPrice = lastOffer.price;
      if(maxOffer->price >= lastOffer.price) // max price is larger than we sell
      {
        transaction->time = lastOffer.time;
        transaction->buyerID = maxOffer->ID;
        transaction->sellerID = lastOffer.ID;
        transaction->price = transPrice;
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
          stock->sellers->find(lastOffer)->shares = lastOffer.shares;
        }
        return true; // made transaction
      }
    }
  }
  return false; // means no more transactions, and transaction will be ignored
} // newTransaction()
