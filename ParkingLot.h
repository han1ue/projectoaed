#include "Defs.h"

typedef struct parkinglot ParkingLot;

ParkingLot * InitParkingLot( FILE *, int, int, int, int);
ParkingLot * MapInit(FILE *);
char *** MatrixInit(int*, FILE *, int, int, int);
int * InitPassages(int,Array, int);
void FreeMatrix(char ***, int, int, int);
