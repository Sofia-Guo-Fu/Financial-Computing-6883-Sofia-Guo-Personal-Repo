CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl -lpthread

all: main

main: main.o ReadData.o Helper.o gnuplot.o
	$(CC) $(CFLAGS) -o main main.o ReadData.o Helper.o gnuplot.o -lcurl

main.o: main.cpp ReadData.h Stock.h Helper.h Calculation.h gnuplot.h
	$(CC) $(CFLAGS) -c main.cpp

ReadData.o: ReadData.cpp ReadData.h Stock.h
	$(CC) $(CFLAGS) -c ReadData.cpp

Helper.o: Helper.cpp Helper.h 
	$(CC) $(CFLAGS) -c Helper.cpp
	
gnuplot.o: gnuplot.cpp gnuplot.h
	$(CC) $(CFLAGS) -c gnuplot.cpp

clean:
	rm -rf main *.o
