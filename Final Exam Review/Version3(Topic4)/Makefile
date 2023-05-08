CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

OptionPricer03: OptionPricer03.o BinomialTreeModel.o Option03.o
	$(CC) $(CFLAGS) -o OptionPricer03 OptionPricer03.o BinomialTreeModel02.o Option03.o

OptionPricer03.o: OptionPricer03.cpp BinomialTreeModel02.h Option03.h
	$(CC) $(CFLAGS) -c OptionPricer03.cpp

Option03.o: BinomialTreeModel02.h Option03.h Option03.cpp
	$(CC) $(CFLAGS) -c Option03.cpp
	
BinomialTreeModel.o: BinomialTreeModel02.h BinomialTreeModel02.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel02.cpp
	
clean:
	rm -rf OptionPricer01 *.o



