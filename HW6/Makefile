CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main: main.o BinomialTreeModel02.o Option08.o
	$(CC) $(CFLAGS) -o main main.o BinomialTreeModel02.o Option08.o

main.o: main.cpp BinomialTreeModel02.h Option08.h BinLattice02.h 
	$(CC) $(CFLAGS) -c main.cpp

Option08.o: BinomialTreeModel02.h Option08.h Option08.cpp BinLattice02.h 
	$(CC) $(CFLAGS) -c Option08.cpp
	
BinomialTreeModel.o: BinomialTreeModel02.h BinomialTreeModel02.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel02.cpp
	
clean:
	rm -rf main *.o



