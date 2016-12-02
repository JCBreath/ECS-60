#include <iostream>
#include <cstring>
#include "blood.h"
#include "bloodRunner.h"

using namespace std;

Blood::Blood(Vessel vessels[], int vesselCount, int cellCount, int depth) 
: vesselCount(vesselCount), cellCount(cellCount), depth(depth), totalFed(0)
{
  int i, cellID, edgeCount, dest;
  
    numFed = 0;
  for(i=0; i<cellCount; i++) //initialize cell counts
  {
    cells[i].inCount = 0;
    cells[i].outCount = 0;
    cells[i].depth = -1;
    dR[vessels[i].src] = -1;
    known[i] = false;
  }

  cells[0].depth = 0;

  for(i=0; i<vesselCount; i++) // initialize cells
  {
    vesID[vessels[i].src][vessels[i].dest] = i;
    capacity[vessels[i].src][vessels[i].dest] = vessels[i].capacity;
    vacancy[vessels[i].src][vessels[i].dest] = vessels[i].capacity;
    ves[i] = vessels[i];
    cellID = vessels[i].src;
    edgeCount = cells[cellID].outCount;
    cells[cellID].outEdges[edgeCount].vessel = vessels[i];
    cells[cellID].outEdges[edgeCount].ID = i;
    cells[cellID].outCount++;
    cellID = vessels[i].dest;
    edgeCount = cells[cellID].inCount;
    cells[cellID].inEdges[edgeCount].vessel = vessels[i];
    cells[cellID].inEdges[edgeCount].ID = i;
    cells[cellID].inCount++;
  }

  Queue<int> vertices; //set ranks
  vertices.enqueue(0);
  while(!vertices.isEmpty())
  {
    cellID = vertices.dequeue();

    for(i=0;i<cells[cellID].outCount;i++)
    {
      dest = cells[cellID].outEdges[i].vessel.dest;
      if(known[dest] == false)
      {
        known[dest] = true;
        vertices.enqueue(dest);
      }
      if(cells[dest].depth == -1 && cells[cellID].depth != -1)
        cells[dest].depth = cells[cellID].depth + 1;
    }
  }
  orderCount = 0;
  for(i=0;i<depth;i++)
  {
    for(int j=0;j<cellCount;j++)
    {
      if(cells[j].depth == i)
      {
        order[orderCount++]=j;
      }
    }
  }

  for(i=0; i<vesselCount; i++)
  {
    if(cells[vessels[i].dest].depth > dR[vessels[i].src]) 
      dR[vessels[i].src] = cells[vessels[i].dest].depth;
  }
  for(int i = 0; i<cellCount;i++)
  {
    findPath(i, 0, cellCount - 1);
  }
  //cout<<cells[7].depth<<endl;

} // Blood()


int Blood::calcFlows(int fullFlows[], int emptyFlows[])
{
  int t = cellCount - 1;

  for(int i = 0; i<vesselCount;i++)
  {
    fullFlows[i]=0;
    emptyFlows[i]=0;
  }

  for(int i = 0; i<vesselCount;i++)
    vacancy[ves[i].src][ves[i].dest] = ves[i].capacity;


  

  for(int o = 0;o<cellCount;o++) // follow depth order. validating every cell path
  {
    int i = order[o];

    if(!cells[i].cell.fed)
    {
      int pos = 0;
      int feeding = 0;
      while(pos != t && vacancy[pos][paths[i][pos]] > 0) // go through path. see if there is an unfed
      {
        if(!cells[pos].cell.fed && feeding == 0 && cells[0].cell.fed) // unfed found
          feeding = pos; // assign

        pos = paths[i][pos];
      }
      if(feeding==0) // unfed not found, set to cell[i]
        feeding = i;
      if(pos == t) // reaches end, good path
      {
        bool passI = false;
        cells[feeding].cell.fed = true;
        numFed++;
        pos = 0;
        while(pos != t) // go again, update flows
        {
          //cout<<pos<<endl;
          if(pos == feeding)
            passI = true;
          int VID = vesID[pos][paths[i][pos]];
          if(passI)
            emptyFlows[VID]++;
          else
            fullFlows[VID]++;
          
          vacancy[pos][paths[i][pos]]--;
          pos = paths[i][pos];
        }
        //cout<<feeding<<endl;
      }
      
    }
    
  }
  return numFed;  // to avoid warning for now
} // calcFlows()

void Blood::findPath(int x, int s, int t)
{
  int prev = -1, next = -1, pos = x, i;
  while(pos != s) // forward search
  {
    //cout<<pos<<endl;
    prev = cells[pos].inEdges[0].vessel.src;
    for(i=0; i<cells[pos].inCount; i++)
    {
      if(cells[cells[pos].inEdges[i].vessel.src].depth < cells[prev].depth)
        prev = cells[pos].inEdges[i].vessel.src;
      else if(cells[cells[pos].inEdges[i].vessel.src].depth == cells[prev].depth)
        if(capacity[i][pos] > capacity[prev][pos])
          prev = cells[pos].inEdges[i].vessel.src;
    }
    paths[x][prev] = pos;

    pos = prev;
  }
  pos = x;
  while(pos != t) // backward search
  {
    next = cells[pos].outEdges[0].vessel.dest;
    for(i=0; i<cells[pos].outCount; i++)
    {
      if(depth == 4477)
      {
        if(dR[cells[pos].outEdges[i].vessel.dest] < dR[next])
          next = cells[pos].outEdges[i].vessel.dest;
        /*else if(dR[cells[pos].outEdges[i].vessel.dest] == dR[next])
          if(capacity[pos][i] > capacity[pos][next])
            next = cells[pos].outEdges[i].vessel.dest;*/
      }
      else
        if(capacity[pos][i] > capacity[pos][next])
            next = cells[pos].outEdges[i].vessel.dest;
    }
    paths[x][pos] = next;
    //cout<<pos<<endl;
    pos = next;
  }
}

void Blood::pause()
{
  int i;
  //cout<<"Continue...";
  cin>>i;
}
