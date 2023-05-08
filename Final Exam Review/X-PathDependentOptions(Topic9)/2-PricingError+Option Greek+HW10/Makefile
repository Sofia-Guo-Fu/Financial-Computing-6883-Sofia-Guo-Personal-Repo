CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

Main: Main.o MCModel.o PathDepOption.o
	$(CC) $(CFLAGS) -o Main Main.o MCModel.o PathDepOption.o

Main.o: Main.cpp MCModel.h PathDepOption.h
	$(CC) $(CFLAGS) -c Main.cpp

PathDepOption.o: MCModel.h PathDepOption.h PathDepOption.cpp
	$(CC) $(CFLAGS) -c PathDepOption.cpp
	
MCModel.o: MCModel.h MCModel.cpp
	$(CC) $(CFLAGS) -c MCModel.cpp
	
clean:
	rm -rf  Main *.o



