#include "Defs.h"

struct parkedcarstruct
{
    char * carid;
    int x;
    int y;
    int z;

};

void OcuppyParkedCars(ParkingLot* parkinglot, FILE* carfile)
{
    char string[MAX_STRING];
    char type;
    int x, y, z;
    int i;

    while(fgets(string, MAX_STRING, carfile) != NULL)
    {
        if (sscanf(string, "%*s %*d %c %d %d %d ", &type, &x, &y, &z) == 4)
        {
            if (type == 'S')
            {
                i = FindIP(GetVertices(parkinglot), x, y, z, GetDecoder(parkinglot));
                OccupyPos(i, GetDecoder(parkinglot), GetVertices(parkinglot));
            }
        }

    }
}

void AddParkedCar(char* carname, int x, int y, int z, ParkingLot* parkinglot)
{
    ParkedCar* parkedcar = (ParkedCar*)malloc(sizeof(ParkedCar));
    parkedcar->carid = carname;
    parkedcar->x = x;
    parkedcar->y = y;
    parkedcar->z = z;

    SetParkedListHead(parkinglot, AddNodeToListHead(GetParkedListHead(parkinglot), (Item) parkedcar));
}
