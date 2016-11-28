#include <iostream>
#include "blood.h"
#include "bloodRunner.h"

using namespace std;

Blood::Blood(Vessel vessels[], int vesselCount, int cellCount, int depth) 
: vesselCount(vesselCount), cellCount(cellCount), depth(depth), totalFed(0)
{
  int i, cellID, edgeCount;

  for(i=0; i<cellCount; i++)
    cells[i].edgeCount = 0;

  for(i=0; i<vesselCount; i++) // initialize cells
  {
    cellID = vessels[i].src;
    edgeCount = cells[cellID].edgeCount;
    cells[cellID].edges[edgeCount].vessel = vessels[i];
    cells[cellID].edges[edgeCount].ID = i;
    cells[cellID].edgeCount++;
  }

  for(i=0; i<cells[0].edgeCount; i++)
    cout<<cells[0].edges[i].vessel.dest<<endl;
  cin>>i;
} // Blood()


int Blood::calcFlows(int fullFlows[], int emptyFlows[])
{

  return 0;  // to avoid warning for now
} // calcFlows()
