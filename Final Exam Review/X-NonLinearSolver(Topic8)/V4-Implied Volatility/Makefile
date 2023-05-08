CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main04: main04.o NonlinearSolver02.o EurCall.o Function02.o
	$(CC) $(CFLAGS) -o main04 main04.o NonlinearSolver02.o EurCall.o Function02.o

main04.o: main04.cpp NonlinearSolver02.h EurCall.o Function02.h 
	$(CC) $(CFLAGS) -c main04.cpp NonlinearSolver02.cpp EurCall.cpp
	
EurCall.o: NonlinearSolver02.h EurCall.h EurCall.cpp
	$(CC) $(CFLAGS) -c NonlinearSolver02.cpp EurCall.cpp

NonlinearSolver02.o: NonlinearSolver02.h NonlinearSolver02.cpp Function02.h 
	$(CC) $(CFLAGS) -c NonlinearSolver02.cpp 
	
clean:
	rm -rf main04 *.o



