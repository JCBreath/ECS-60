#include <iostream>
#include <fstream>
#include "CPUTimer.h"

#include "LinkedList.h"
#include "CursorList.h"
#include "StackAr.h"
#include "StackLi.h"
#include "QueueAr.h"
#include "SkipList.h"


//using namespace std;

int getChoice()
{
  int choice;
  cout << endl;
  cout << "      ADT Menu" << endl;
  cout << "0. Quit" << endl;
  cout << "1. LinkedList" << endl;
  cout << "2. CursorList" << endl;
  cout << "3. StackAr" << endl;
  cout << "4. StackLi" << endl;
  cout << "5. QueueAr" << endl;
  cout << "6. SkipList" << endl;
  cout << "Your choice >> ";
  cin >> choice;
  return choice;
}



void RunList(string filename)
{
  ifstream file(filename);
  string str;
  char op;
  int value;
  getline(file, str);
  str = "";
  List<int> list = List<int>();
  while(file >> op >> value)
  {
    if(op == 'i')
      list.insert(value, list.zeroth());
    else
      list.remove(value);
  }
}

void RunCursorList(string filename)
{
  ifstream file(filename);
  string str;
  char op;
  int value;
  getline(file, str);
  vector<CursorNode<int>> cursorSpace(500001);
  CursorList<int> list(cursorSpace);
  while(file >> op >> value)
  {
    if(op == 'i')
      list.insert(value, list.zeroth());
    else
      list.remove(value);
  }
}


void RunStackAr(string filename)
{
  ifstream file(filename);
  string str;
  char op;
  int value;
  getline(file, str);
  StackAr<int> s(500001);
  while(file >> op >> value)
  {
    if(op == 'i')
      s.push(value);
    else
      s.pop();
  }
}


void RunStackLi(string filename)
{
  ifstream file(filename);
  string str;
  char op;
  int value;
  getline(file, str);
  StackLi<int> s;
  while(file >> op >> value)
  {
    if(op == 'i')
      s.push(value);
    else
      s.pop();
  }
}


void RunQueueAr(string filename)
{
  ifstream file(filename);
  string str;
  char op;
  int value;
  getline(file, str);
  Queue<int> q(500001);
  while(file >> op >> value)
  {
    if(op == 'i')
      q.enqueue(value);
    else
      q.dequeue();
  }
}

void RunSkipList(string filename)
{
  ifstream file(filename);
  string str;
  char op;
  int value, i;
  getline(file, str);
  SkipList<int> sl(i, 500001);
  while(file >> op >> value)
  {
    if(op == 'i')
      sl.insert(value);
    else
      sl.deleteNode(value);
  }
}


main()
{  
  string filename;
  cout << "Filename >> ";
  cin >> filename;

  CPUTimer ct;
  int choice;

  do
  {
    choice = getChoice();
    ct.reset();
    switch (choice)
    {
      case 1: RunList(filename); break;
      case 2: RunCursorList(filename); break;
      case 3: RunStackAr(filename); break;
      case 4: RunStackLi(filename); break;
      case 5: RunQueueAr(filename); break;
      case 6: RunSkipList(filename); break;
    }
    
    cout << "CPU time: " << ct.cur_CPUTime() << endl;
  } while(choice > 0);
}

