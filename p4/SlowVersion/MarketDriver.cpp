// Author: Sean Davis

#include <iostream>
#include <fstream>
#include <cstring>
#include "MarketDriver.h"
#include "market.h"
#include "CPUTimer.h"
using namespace std;

Offer::Offer()
{
} // Offer default constructor

Offer::Offer(int t, int I, double pr, int shar, const char *sym, char typ) :
  time(t), ID(I), price(pr), shares(shar), type(typ)
{
  strcpy(symbol, sym);
} // Offer standard constructor

Transaction::Transaction()
{
} // Transaction default constructor

Transaction::Transaction(int t, int buyer, int seller, double pr, int shar,
  const char *sym) : time(t), buyerID(buyer), sellerID(seller), price(pr),
    shares(shar)
{
  strcpy(symbol, sym);
} // Transaction standard constructor

ostream& operator<< (ostream &os, const Transaction &transaction)
{
  os << transaction.time << ' ' << transaction.buyerID << ' '
    << transaction.sellerID << ' ' << transaction.price << ' '
    << transaction.shares << ' ' << transaction.symbol << endl;

  return os;
} // operator<<

istream& operator>> (istream &is, Transaction &transaction)
{
  is >> transaction.time >> transaction.buyerID >> transaction.sellerID
    >> transaction.price >> transaction.shares;
  is.ignore(1);
  is.getline(transaction.symbol, 7);

  return is;
} // operator>>

Offer* readFiles(char *filename, int *numStocks, int *offerCount,
  int *IDs, Transaction **transactions, int *solutionCount)
{
  char transactionFilename[80];
  ifstream inf(filename);
  inf >> *numStocks >> *offerCount >> *IDs;
  inf.ignore(2, '\n');
  Offer *offers = new Offer[*offerCount];
  for(int i = 0; i < *offerCount; i++)
  {
    offers[i].time = i;
    inf >> offers[i].type >> offers[i].ID >> offers[i].price >> offers[i].shares;
    inf.ignore(1);
    inf.getline(offers[i].symbol, 7);
  } // for each offer

  inf.close();

  strtok(filename, ".");
  sprintf(transactionFilename, "%s.sol", filename);
  ifstream inf2(transactionFilename);
  *solutionCount = 0;

  if(inf2) // if there is a solution file
  {
    inf2 >> *solutionCount;
    *transactions = new Transaction[*solutionCount + 2];

    for(int i = 0; i < *solutionCount; i++)
      inf2 >> (*transactions)[i];

   strcpy((*transactions)[*solutionCount].symbol, "NONE");
  } // if there is a solution file

  return offers;
} // readFiles()

void checkTransaction(const Transaction *transactions,
  const Transaction *solutionTransactions, int transactionCount)
{
  if(transactions[transactionCount].time 
    != solutionTransactions[transactionCount].time)
      cout << "Time error at transaction #" << transactionCount << endl;

  if(transactions[transactionCount].buyerID 
    != solutionTransactions[transactionCount].buyerID)
      cout << "buyerID error at transaction #" << transactionCount << endl;

  if(transactions[transactionCount].sellerID 
    != solutionTransactions[transactionCount].sellerID)
      cout << "sellerID error at transaction #" << transactionCount << endl;

 if(transactions[transactionCount].price <
    solutionTransactions[transactionCount].price - 0.01
   || transactions[transactionCount].price >
    solutionTransactions[transactionCount].price + 0.01
   )
      cout << "price error at transaction #" << transactionCount << endl;

 if(transactions[transactionCount].shares 
   != solutionTransactions[transactionCount].shares)
      cout << "shares error at transaction #" << transactionCount << endl;

 if(strcmp(transactions[transactionCount].symbol, 
   solutionTransactions[transactionCount].symbol))
      cout << "symbol error at transaction #" << transactionCount << endl;
} // checkTransaction()

void writeSolutions(char *filename, Transaction *transactions, 
  int transactionCount)
{
  char solutionFilename[80];
  strcpy(solutionFilename, strtok(filename, "."));
  strcat(solutionFilename, ".sol");
  ofstream outf(solutionFilename);
  outf << transactionCount << endl;
  
  for(int i = 0; i < transactionCount; i++)
    outf << transactions[i];
  
  outf.close();
}  // writeSolutions()



int main(int argc, char* argv[])
{
  int numStocks, offerCount, IDs, solutionCount, transactionCount = 0, i;
  double time;
  Transaction transaction, *solutionTransactions, *transactions;
  Offer *offers = readFiles(argv[1], &numStocks, &offerCount, &IDs,
    &solutionTransactions, &solutionCount);
  transactions = new Transaction[1000000];
  CPUTimer ct;
  Market *market = new Market(numStocks, offerCount, IDs);

  for(int i = 0; i < offerCount; i++)
  {
    market->newOffer(offers[i]);
   
    while(market->newTransaction(&transactions[transactionCount]) 
      && transactionCount < 1000000)
       transactionCount++;
  }  // for each offer
  
  time = ct.cur_CPUTime();
  
  if(solutionCount > 0)  // used by students with .sol file already existing.
  {
    for(i = 0; i < transactionCount  && i < solutionCount; i++)
      checkTransaction(transactions, solutionTransactions, i);
    
    if(transactionCount < solutionCount)
      cout << "Too few transactions.\n";
    else
      if(transactionCount > solutionCount)
        cout << "Too many transactions.\n";
  } // for each offer;
  else  // write a solution file.
    writeSolutions(argv[1], transactions, transactionCount);
      
  cout << "CPU: " << time << endl;
  delete market;
  return 0;
} // main()

