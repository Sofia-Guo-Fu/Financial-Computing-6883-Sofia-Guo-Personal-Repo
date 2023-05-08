CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

Main01: Main01.o PathDepOption.o MCModel.o
	$(CC) $(CFLAGS) -o Main01 Main01.o PathDepOption.o MCModel.o

Main01.o: Main01.cpp PathDepOption.h MCModel.h
	$(CC) $(CFLAGS) -c Main01.cpp PathDepOption.cpp MCModel.cpp
	
PathDepOption.o: PathDepOption.h MCModel.h MCModel.cpp
	$(CC) $(CFLAGS) -c PathDepOption.cpp MCModel.cpp

MCModel.o: MCModel.h MCModel.cpp
	$(CC) $(CFLAGS) -c MCModel.cpp
	
clean:
	rm -rf Main01 *.o



