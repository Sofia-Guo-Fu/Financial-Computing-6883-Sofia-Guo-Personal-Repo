CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

OptionPricer07: OptionPricer07.o BinomialTreeModel02.o Option07.o
	$(CC) $(CFLAGS) -o OptionPricer07 OptionPricer07.o BinomialTreeModel02.o Option07.o

OptionPricer07.o: OptionPricer07.cpp BinomialTreeModel02.h Option07.h BinLattice01.h 
	$(CC) $(CFLAGS) -c OptionPricer07.cpp

Option07.o: BinomialTreeModel02.h Option07.h Option07.cpp BinLattice01.h 
	$(CC) $(CFLAGS) -c Option07.cpp
	
BinomialTreeModel.o: BinomialTreeModel02.h BinomialTreeModel02.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel02.cpp
	
clean:
	rm -rf OptionPricer07 *.o



