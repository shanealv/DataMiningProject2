CC = g++
CFLAGS = -std=c++0x -g
BIN = bin/
DBSCAN = ./src/dbscan/
KMEANS = ./src/kmeans/

all: bin dbscan kmeans

bin:
	mkdir bin

#kmeans
kmeans: kmeans_main.d kmeans.d
	$(CC) $(CFLAGS) -o kmeans.exe $(BIN)kmeans_main.o $(BIN)kmeans.o

kmeans_main.d: $(KMEANS)kmeans.h
	$(CC) $(CFLAGS) -c $(KMEANS)kmeans_main.cpp -I $(KMEANS) -o $(BIN)kmeans_main.o

kmeans.d: $(KMEANS)kmeans.h
	$(CC) $(CFLAGS) -c $(KMEANS)kmeans.cpp -I $(KMEANS) -o $(BIN)kmeans.o

#dbscan
dbscan: dbscan_main.d dbscan.d clusternode.d
	$(CC) $(CFLAGS) -o dbscan.exe $(BIN)dbscan_main.o $(BIN)dbscan.o $(BIN)clusternode.o

dbscan_main.d:
	$(CC) $(CFLAGS) -c $(DBSCAN)dbscan_main.cpp  -I $(DBSCAN) -o $(BIN)dbscan_main.o

dbscan.d:
	$(CC) $(CFLAGS) -c $(DBSCAN)dbscan.cpp  -I $(DBSCAN) -o $(BIN)dbscan.o

clusternode.d:
	$(CC) $(CFLAGS) -c $(DBSCAN)clusternode.cpp  -I $(DBSCAN) -o $(BIN)clusternode.o

clean:
	rm -f -r bin 

rebuild: clean all
