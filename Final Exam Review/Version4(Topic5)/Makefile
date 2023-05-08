CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

OptionPricer04: OptionPricer04.o BinomialTreeModel02.o Option04.o
	$(CC) $(CFLAGS) -o OptionPricer04 OptionPricer04.o BinomialTreeModel02.o Option04.o

OptionPricer04.o: OptionPricer04.cpp BinomialTreeModel02.h Option04.h
	$(CC) $(CFLAGS) -c OptionPricer04.cpp

Option04.o: BinomialTreeModel02.h Option04.h Option04.cpp
	$(CC) $(CFLAGS) -c Option04.cpp
	
BinomialTreeModel.o: BinomialTreeModel02.h BinomialTreeModel02.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel02.cpp
	
clean:
	rm -rf OptionPricer04 *.o



