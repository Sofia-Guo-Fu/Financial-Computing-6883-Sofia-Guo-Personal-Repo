CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main02: main02.o NonlinearSolver02.o Function02.o
	$(CC) $(CFLAGS) -o main02 main02.o NonlinearSolver02.o Function02.o

main02.o: main02.cpp NonlinearSolver02.h Function02.h 
	$(CC) $(CFLAGS) -c main02.cpp NonlinearSolver02.cpp Function02.cpp

NonlinearSolver02.o: NonlinearSolver02.h NonlinearSolver02.cpp Function02.h 
	$(CC) $(CFLAGS) -c NonlinearSolver02.cpp Function02.cpp 
	
Function02.o: Function02.h Function02.cpp
	$(CC) $(CFLAGS) -c Function02.cpp
	
clean:
	rm -rf main02 *.o



