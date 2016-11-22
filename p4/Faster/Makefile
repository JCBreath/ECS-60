market.out : BinaryHeap.o market.o MarketDriver.o QuadraticProbing.o  
	g++ -ansi -Wall  -o market.out BinaryHeap.o market.o MarketDriver.o QuadraticProbing.o  

BinaryHeap.o : BinaryHeap.cpp BinaryHeap.h MarketDriver.h 
	g++ -ansi -Wall  -c BinaryHeap.cpp

market.o : market.cpp market.h MarketDriver.h BinaryHeap.h QuadraticProbing.h BinarySearchTree.h 
	g++ -ansi -Wall  -c market.cpp

MarketDriver.o : MarketDriver.cpp MarketDriver.h market.h CPUTimer.h 
	g++ -ansi -Wall  -c MarketDriver.cpp

QuadraticProbing.o : QuadraticProbing.cpp QuadraticProbing.h 
	g++ -ansi -Wall  -c QuadraticProbing.cpp

clean : 
	rm -f market.out BinaryHeap.o market.o  MarketDriver.o  QuadraticProbing.o   
