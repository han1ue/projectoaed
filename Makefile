CC=gcc
CFLAGS= -Wall -ansi -O3
DEPS = client.h ArrayList.h Dijkstra.h Graph.h HandleCar.h Heap.h InterestPoint.h LinkedList.oh Output.h ParkedCar.h ParkingLot.h RestList.h Adjacency.h Defs.h
OBJ = client.o ArrayList.o Dijkstra.o Graph.o HandleCar.o Heap.o InterestPoint.o LinkedList.o Output.o ParkedCar.o ParkingLot.o RestList.o Adjacency.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

autopark: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)