CC = g++
CFLAGS = -std=c++0x -g

all: main.o dbscan.o clusternode.o
	$(CC) $(CFLAGS) -o dbscan.exe main.o dbscan.o clusternode.o

main.o: dbscan.h
	$(CC) $(CFLAGS) -c main.cpp

dbscan.o: dbscan.h clusternode.h
	$(CC) $(CFLAGS) -c dbscan.cpp

clusternode.o: clusternode.h
	$(CC) $(CFLAGS) -c clusternode.cpp

clean:
	rm -f *.o dbscan.exe

rebuild: clean all