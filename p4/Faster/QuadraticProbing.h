#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

class StockIndex
{
public:
  char symbol[7];
  int index;
  StockIndex() {symbol[0] = 0;}
};

class QuadraticHashTable
{
  public:
    explicit QuadraticHashTable(int sz ): size(sz), count(0) 
      {array = new StockIndex[size];}
    int find(const char *symbol);
  private:
    StockIndex *array;
    int size;
    int count;
};

#endif
