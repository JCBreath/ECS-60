// Author: Sean Davis
#ifndef bloodH
#define bloodH

#include "bloodRunner.h"

class Edge
{
public:
  Vessel vessel;
  int ID;
};

class Vertex
{
public:
  Cell cell;
  int edgeCount;
  Edge edges[4]; // outflow vessel (max 5)
};

class Blood
{
public:
  Blood(Vessel vessels[], int vesselCount, int cellCount, int depth);
  int vesselCount, cellCount, depth, totalFed;
  Vertex cells[5000];
  int calcFlows(int fullFlows[], int emptyFlows[]);
}; // class Blood


#endif
