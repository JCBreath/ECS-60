// Author: Sean Davis
#include<cstring>
#include "market.h"
#include "MarketDriver.h"
#include "BinaryHeap.h"
#include "QuadraticProbing.h"
using namespace std;

Market::Market(int numStocks, int offerCount, int IDs) : symbolTable(numStocks * 2)
{
  buyingHeaps = new BinaryHeap[numStocks];
  sellingLists = new Offer*[numStocks];
  
  for(int i = 0; i < numStocks; i++)
  {
    counts[i] = 0;
    sellingLists[i] = new Offer[offerCount / numStocks + 3];
  }
} // Market()

void Market::newOffer(const Offer &offer)
{
  stockIndex = symbolTable.find(offer.symbol); 
  time  = offer.time;
  
  if(offer.type == 'B')
    buyingHeaps[stockIndex].insert(offer);
  else
    sellingLists[stockIndex][counts[stockIndex]++] = offer;
    
} // newOffer()


bool Market::newTransaction(Transaction *transaction)
{
  int i, bestSellerIndex = -1;
  Offer *sellingList = sellingLists[stockIndex];
  
  if(buyingHeaps[stockIndex].isEmpty())
    return false;
  
  Offer2 &offer = buyingHeaps[stockIndex].findMax();
  double price = offer.offer->price;
  
  for(i = 0; i < counts[stockIndex]; i++)  // find an ask <= bid
    if(sellingList[i].price <= price)
    {
      bestSellerIndex = i;
      break;
    }  // if ask <= bid
  
  if(bestSellerIndex == -1)
    return false;  // no ask <= bid found.
  
  for( ; i < counts[stockIndex]; i++)
    if(sellingList[i].price <= price
      && (sellingList[i].price > sellingList[bestSellerIndex].price
      || (sellingList[i].price == sellingList[bestSellerIndex].price && sellingList[i].time < sellingList[bestSellerIndex].time)))
      bestSellerIndex = i;
  
  transaction->time = time;
  transaction->buyerID = offer.offer->ID;
  transaction->sellerID = sellingList[bestSellerIndex].ID;
  strcpy(transaction->symbol, offer.offer->symbol);
  price  = buyingHeaps[stockIndex].findSecondPrice();
  
  if(price >= sellingList[bestSellerIndex].price)
    transaction->price = price;  // price of next bidder
  else
    transaction->price = sellingList[bestSellerIndex].price;


  if(offer.shares <= sellingList[bestSellerIndex].shares)
  {
    transaction->shares = offer.shares;
        
    if(offer.shares == sellingList[bestSellerIndex].shares)
    {
      if(--counts[stockIndex] > 0)
        sellingList[bestSellerIndex] = sellingList[counts[stockIndex]];  // remove seller
    }
    else
      sellingList[bestSellerIndex].shares -= offer.shares;
    
    buyingHeaps[stockIndex].deleteMax();
  }  // if buyer buying less than or equal seller has  
  else  // buyer buying > seller
  {
     transaction->shares = sellingList[bestSellerIndex].shares;

     if(--counts[stockIndex] > 0)
       sellingList[bestSellerIndex] = sellingList[counts[stockIndex]];  // remove seller
     
     offer.shares -= transaction->shares;
  }  // else buying shares >= seller shares
  
  return true;
} // newTransaction()
