CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main03: main03.o Function03.o
	$(CC) $(CFLAGS) -o main03 main03.o Function03.o

main03.o: main03.cpp NonlinearSolver03.h Function03.h 
	$(CC) $(CFLAGS) -c main03.cpp Function03.cpp

# NonlinearSolver03.o: NonlinearSolver03.h Function03.h 
# 	$(CC) $(CFLAGS) -c Function03.cpp 
	
Function03.o: Function03.h Function03.cpp
	$(CC) $(CFLAGS) -c Function03.cpp
	
clean:
	rm -rf main03 *.o



