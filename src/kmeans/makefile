# k means
CC = g++
CFLAGS = -std=c++0x -g

all: main.o kmeans.o
	$(CC) $(CFLAGS) -o kmeans.exe main.o kmeans.o

main.o: kmeans.h
	$(CC) $(CFLAGS) -c main.cpp

kmeans.o: kmeans.h
	$(CC) $(CFLAGS) -c kmeans.cpp

clean:
	rm -f *.o kmeans.exe

rebuild: clean all
