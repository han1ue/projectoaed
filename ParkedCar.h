#include "Defs.h"

typedef struct parkedcarstruct ParkedCar;

void OcuppyParkedCars(ParkingLot*, FILE*);
void AddParkedCar(char*, int, int, int, ParkingLot*);
void GetParkedCarCoords(ParkingLot*, char*, int*, int*, int*);
