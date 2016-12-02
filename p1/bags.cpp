#include <iostream>
#include <fstream>
#include <cstdlib>

#include "StackAr.h"
#include "QueueAr.h"

using namespace std;

int main(int argc, char* argv[])
{
  ifstream file(argv[1]);
  int qSize = atoi(argv[2]);
  StackAr<Queue<int>*> s(1000);
  short bagNum;
  Queue<int> *q = new Queue<int>(qSize);

  while(file >> bagNum)
  {
    if(!q->isFull())
    {
      q->enqueue(bagNum);
    }
    else
    {
      s.push(q);
      q = new Queue<int>(qSize);
      q->enqueue(bagNum);
    }
  }
  s.push(q);

  while(!s.isEmpty())
  {
    while(!s.top()->isEmpty())
    {
      cout << s.top()->dequeue() << " ";
    }
    s.pop();
  }
  cout << endl;

}