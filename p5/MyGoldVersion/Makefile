blood.out: blood.o bloodRunner.o
	g++ -Wall -ansi -g -o blood.out blood.o bloodRunner.o 

blood.o: blood.cpp blood.h bloodRunner.h 
	g++ -Wall -ansi -g -c blood.cpp

bloodRunner.o: bloodRunner.cpp bloodRunner.h CPUTimer.h blood.h  
	g++ -Wall -ansi -g -c bloodRunner.cpp

clean:
	rm -f blood.out blood.o bloodRunner.o 
