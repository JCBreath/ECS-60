market.out : market.o MarketDriver.o  
	g++ -ansi -Wall -g -o market.out market.o MarketDriver.o  

market.o : market.cpp market.h MarketDriver.h 
	g++ -ansi -Wall -g -c market.cpp

MarketDriver.o : MarketDriver.cpp MarketDriver.h market.h CPUTimer.h 
	g++ -ansi -Wall -g -c MarketDriver.cpp

clean : 
	rm -f market.out market.o  MarketDriver.o   
