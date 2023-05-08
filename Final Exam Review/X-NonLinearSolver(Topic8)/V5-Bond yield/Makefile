CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main: main.o NonlinearSolver02.o Bond.o Function02.o
	$(CC) $(CFLAGS) -o main main.o NonlinearSolver02.o Bond.o Function02.o

main.o: main.cpp NonlinearSolver02.h Bond.o Function02.h 
	$(CC) $(CFLAGS) -c main.cpp NonlinearSolver02.cpp Bond.cpp
	
Bond.o: Bond.h Bond.cpp Function02.h
	$(CC) $(CFLAGS) -c Bond.cpp

NonlinearSolver02.o: NonlinearSolver02.h NonlinearSolver02.cpp Function02.h 
	$(CC) $(CFLAGS) -c NonlinearSolver02.cpp 

Function02.o: Function02.h Function02.cpp
	$(CC) $(CFLAGS) -c Function02.cpp 
	
clean:
	rm -rf main04 *.o



