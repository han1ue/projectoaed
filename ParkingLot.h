#include "Defs.h"

typedef struct parkinglot ParkingLot;

ParkingLot * InitParkingLot( FILE *, int, int, int, int);
ParkingLot * MapInit(FILE *);
char *** MatrixInit(int*, int*, FILE *, int, int, int);
ListNode * InitAccesses(int, Array, int);
int * InitRamps(int, Array, int);
void FreeMatrix(char ***, int, int, int);
Graph* GetGraph(ParkingLot*);
int GetVertices(ParkingLot*);
Array GetDecoder(ParkingLot*);
ListNode * GetAccesses(ParkingLot*);
int GetFreeSpots(ParkingLot* parkinglot);
void IncFreeSpots(ParkingLot* parkinglot);
void DecFreeSpots(ParkingLot* parkinglot);
ListNode* GetParkedListHead(ParkingLot*);
void SetParkedListHead(ParkingLot*, ListNode*);
ListNode * RemoveListHead(ListNode* );
