// Author: Sean Davis
#include<cstring>
#include "market.h"
#include "MarketDriver.h"
#include "BinaryHeap.h"
#include "QuadraticProbing.h"
#include "BinarySearchTree.h"
using namespace std;

Market::Market(int numStocks, int offerCount, int IDs) : symbolTable(numStocks + 2000)
{
  buyingHeaps = new BinaryHeap[numStocks];
  sellingTrees = new BinarySearchTree[numStocks];
} // Market()

void Market::newOffer(const Offer &offer)
{
  stockIndex = symbolTable.find(offer.symbol); 
  time  = offer.time;
  
  if(offer.type == 'B')
    buyingHeaps[stockIndex].insert(offer);
  else
    sellingTrees[stockIndex].insert(offer);
    
} // newOffer()


bool Market::newTransaction(Transaction *transaction)
{
  if(buyingHeaps[stockIndex].isEmpty())
    return false;
  
  Offer2 &buyingOffer2 = buyingHeaps[stockIndex].findMax();
  Offer2 *sellingOffer2 = sellingTrees[stockIndex].find(buyingOffer2.offer->price);
  
  if(sellingOffer2 == NULL)
    return false;  // no ask <= bid found.
  
  transaction->time = time;
  transaction->buyerID = buyingOffer2.offer->ID;
  transaction->sellerID = sellingOffer2->offer->ID;
  strcpy(transaction->symbol, buyingOffer2.offer->symbol);
  double price  = buyingHeaps[stockIndex].findSecondPrice();
  
  if(price >= sellingOffer2->offer->price)
    transaction->price = price;  // price of next bidder
  else
    transaction->price = sellingOffer2->offer->price;
  
  if(buyingOffer2.shares <= sellingOffer2->shares)
  {
    transaction->shares = buyingOffer2.shares;
    
    if(buyingOffer2.shares == sellingOffer2->shares)
      sellingTrees[stockIndex].remove(sellingOffer2->priceTime);
    else
      sellingOffer2->shares -= buyingOffer2.shares;
    
    buyingHeaps[stockIndex].deleteMax();
  }  // if buyer buying less than or equal to what seller has  
  else  // buyer buying > seller
  {
     transaction->shares = sellingOffer2->shares;
     buyingOffer2.shares  -= transaction->shares; 
     sellingTrees[stockIndex].remove(sellingOffer2->priceTime);
  }  // else buying shares > seller shares
  
  return true;
} // newTransaction()
