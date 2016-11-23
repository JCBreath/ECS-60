#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

void readSymbols(char symbols[3792][7], double basePrices[3792],
  int numberOfStocks)
{
  char line[80];
  ifstream inf("nysesym.csv");

  for(int i = 0; i < 3792; i++)
  {
    inf.getline(line, 80);
    strtok(line, ",");
    strcpy(symbols[i], line);
    basePrices[i] = (rand() % 30000 + 300) / 100.0;
  } // for every stock

  for(int i = 0; i < numberOfStocks; i++)
  {
    int stock1 = rand() % 3792;
    strcpy(line, symbols[i]);
    strcpy(symbols[i], symbols[stock1]);
    strcpy(symbols[stock1], line);
  } // for numberOfStocks
} // readSymbols()

int main()
{
  int seed, numberOfStocks, offers, stock, IDs;
  char filename[80], symbols[3792][7];
  double basePrices[3792], price;
  do
  {
    cout << "Number of stocks (1 - 3792): ";
    cin >> numberOfStocks;
  } while(numberOfStocks < 1 || numberOfStocks > 3792);

  cout << "Number of Offers (1 - 1,000,000): ";
  cin >> offers;
  cout << "Number of IDs (1 - 100,000): ";
  cin >> IDs;
  cout << "Seed (1 - 100): ";
  cin >> seed;
  srand(seed);
  readSymbols(symbols, basePrices, numberOfStocks);
  sprintf(filename, "market-%d-%d-%d-%d.txt", numberOfStocks, offers, IDs, seed);
  ofstream outf(filename);

  outf << numberOfStocks << ' ' << offers << ' ' << IDs << endl;
  for(int i = 0; i < offers; i++)
  {
    if(rand() % 2 == 0)
      outf << 'B'; // buy
    else
      outf << 'S'; // sell
    outf << rand() % IDs << ' ';

    stock = rand() % numberOfStocks;
    price = basePrices[stock] * ((rand() % 30000 - 15000.0) / 150000.0 + 1.0);
      // basePrices +- 10%
    outf << fixed << setprecision(2) << price << ' '
    << rand() % 20000 + 100 << ' ' << symbols[stock] << endl;
  } // for row


  return 0;
}  // main()

