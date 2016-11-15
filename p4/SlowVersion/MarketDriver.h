#ifndef MARKETDRIVER_H
  #define MARKETDRIVER_H

#include <iostream>
using namespace std;

class Offer
{
public:
  int time;
  int ID;
  double price;
  int shares;
  char symbol[7];
  char type;  // B = buy, S = sell
  Offer(); // default constructor
  Offer(int t, int I, double pr, int shar, const char *sym, char typ);
}; // class Offer

class Transaction
{
public:
  int time;
  int buyerID;
  int sellerID;
  double price;
  int shares;
  char symbol[7];
  Transaction();
  Transaction(int t, int buyer, int seller, double pr, int shar, const char *sym);
  friend ostream& operator<< (ostream &os, const Transaction &transaction);
  friend istream& operator>> (istream &is, Transaction &transaction);
}; // class Transaction

#endif
