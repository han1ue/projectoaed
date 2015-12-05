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
    parkedcar->carid = (char*) malloc( sizeof(char) * (strlen(carname) + 1) );
    parkedcar->x = x;
    parkedcar->y = y;
    parkedcar->z = z;

    strcpy(parkedcar->carid, carname);

    SetParkedListHead(parkinglot, AddNodeToListHead(GetParkedListHead(parkinglot), (Item) parkedcar));

}

void GetParkedCarCoords(ParkingLot * parkinglot, char * carid, int * x, int * y, int * z)
{
  ListNode * parkedcarhead, *aux;

  parkedcarhead = GetParkedListHead(parkinglot);

  aux = parkedcarhead;

  while( strcmp ( ( (ParkedCar*) getItemLinkedList(aux) ) -> carid , carid ) != 0)
    aux = getNextNodeLinkedList(aux);

  *x = ( (ParkedCar*) getItemLinkedList(aux) ) -> x;
  *y = ( (ParkedCar*) getItemLinkedList(aux) ) -> y;
  *z = ( (ParkedCar*) getItemLinkedList(aux) ) -> z;

}

void PrintParkedCars(ParkingLot * parkinglot)
{
    ListNode * parkedcarhead = GetParkedListHead(parkinglot);
    ListNode * aux;
    ParkedCar * parkedcar;

    for(aux = parkedcarhead; aux != NULL; aux = getNextNodeLinkedList(aux) )
    {
        parkedcar = (ParkedCar*) getItemLinkedList(aux);

        printf("%s %d %d %d\n", parkedcar->carid, parkedcar->x, parkedcar->y, parkedcar->z);
    }
}
