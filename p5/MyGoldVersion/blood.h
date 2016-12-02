// Author: Sean Davis
#ifndef bloodH
#define bloodH

#include "bloodRunner.h"
#include "QueueAr.h"

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
  int depth; // rank
  int inCount, outCount;
  Edge inEdges[5]; // inflow vessel (max 5)
  Edge outEdges[5]; // outflow vessel (max 5)
};

class Blood
{
public:
  Blood(Vessel vessels[], int vesselCount, int cellCount, int depth);
  int vesselCount, cellCount, depth, totalFed;
  void findPath(int x, int s, int t);
  Vertex cells[5000];
  int known[5000];
  int paths[10000][10000]; //shortest path for every node [pathnum][src] = dest
  int dR[5000]; // deepest node connect to this tree
  int numFed; // num of fed cells
  int anyFed; // any fed on this path
  int route[50]; // where this node goes next in this path
  Vessel ves[10000];
  int order[10000];
  int orderCount;
  int capacity[10000][10000];
  int fullVacancy[10000];
  int vesID[10000][10000];
  int vacancy[10000][10000]; // capacity left [src][dest]
  int calcFlows(int fullFlows[], int emptyFlows[]);
  void pause();
}; // class Blood


#endif
