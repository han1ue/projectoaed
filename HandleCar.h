#include "Defs.h"

typedef struct carstruct Car;

int HandleCar(ParkingLot*, FILE*, FILE*, int);
void GetParkedCarCoords(ParkingLot*, char*, int*, int*, int*);
void HandleQueue(ParkingLot *, FILE*);
