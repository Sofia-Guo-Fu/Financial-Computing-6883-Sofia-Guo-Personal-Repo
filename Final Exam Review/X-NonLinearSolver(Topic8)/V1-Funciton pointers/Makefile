CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main01: main01.o NonlinearSolver01.o Function01.o
	$(CC) $(CFLAGS) -o main01 main01.o NonlinearSolver01.o Function01.o

main01.o: main01.cpp NonlinearSolver01.h Function01.h 
	$(CC) $(CFLAGS) -c main01.cpp NonlinearSolver01.cpp Function01.cpp

NonlinearSolver01.o: NonlinearSolver01.h NonlinearSolver01.cpp Function01.h 
	$(CC) $(CFLAGS) -c NonlinearSolver01.cpp Function01.cpp 
	
Function01.o: Function01.h Function01.cpp
	$(CC) $(CFLAGS) -c Function01.cpp
	
clean:
	rm -rf main01 *.o



