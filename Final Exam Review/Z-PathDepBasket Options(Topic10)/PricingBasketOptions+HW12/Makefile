CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

Main: Main.o MCModel02.o PathDepOption02.o Matrix.o
	$(CC) $(CFLAGS) -o Main Main.o MCModel02.o PathDepOption02.o Matrix.o

Main.o: Main.cpp PathDepOption02.h
	$(CC) $(CFLAGS) -c Main.cpp

PathDepOption02.o: MCModel02.h PathDepOption02.h PathDepOption02.cpp
	$(CC) $(CFLAGS) -c PathDepOption02.cpp
	
MCModel2.o: Matrix.h MCModel02.h MCModel02.cpp
	$(CC) $(CFLAGS) -c MCModel02.cpp
	
Matrix.o: Matrix.h Matrix.cpp
	$(CC) $(CFLAGS) -c Matrix.cpp
	
clean:
	rm -rf  Main *.o
