#include "Defs.h"

struct carstruct
{
    char * carid;
    int status;  /*status 1 means active car; status 2 means already parked car; status 3 means car already left the park*/
    ListNode* carpath; /*List that will contain the path from the entry to the parkingspot */
    ListNode* footpath;  /*List that will contain the path from the parkingspot to the access */
};

Car* CarListInit(Event * eventlisthead, ParkingLot * parkinglot)
{
    Car * head, * new_car;
    ListNode* aux;
    Event* auxevent;
    char* carname;
    int i;
    Array decoder = GetDecoder(parkinglot);
    int vertices = GetVertices(parkinglot);

    if(eventlisthead == NULL)
    {
        printf("The event list is empty. There are no cars to add.");
        return NULL;
    }

    head = ListInit(head);
    aux = eventlisthead;

    while (aux != NULL)
    {
        auxevent = (Event*) getItemLinkedList(aux);
        if(GetEventType(auxevent) == 'S' && GetEventFlag(auxevent) != 'g') /*Puts the cars already parked (not put in there by gestor) in the car array */
        {
            new_car = (Car*) malloc( sizeof(Car) );
            carname = (char*)malloc(sizeof(char));
            carname = GetEventCar(auxevent);
            //strcpy((new_car->carid),carname);
            new_car->carid = carname;
            new_car->status = 2;
            new_car->carpath = ListInit(new_car->carpath);
            new_car->footpath = ListInit(new_car->footpath);
            head = AddNodeToListHead(head, (Item) new_car);
          	i = FindIP(vertices, GetEventCoord(auxevent, 'x'), GetEventCoord(auxevent, 'y'), GetEventCoord(auxevent, 'z'), decoder);
            OccupyPos(i, decoder, vertices); /*This funcion will mark the spot (x,y,z) as occupied in the parking lot */
        }
        aux = getNextNodeLinkedList(aux);
    }

    return head;
}


char GetCarStatus(Car* car)
{
    return car->status;
}

int CompareCarStatus(Item car1, Item car2, int direction)
{
    int r;

    if (direction == 1)
    {
        if (GetCarStatus((Car*) car1) > GetCarStatus((Car*) car2))
            r = 1 ;
        else
            r = 0;
    }
    else if (direction == 2)
    {
        if (GetCarStatus((Car*) car1) > GetCarStatus((Car*) car2))
            r = 0 ;
        else
            r = 1;
    }
    return r;
}

char * GetCarID(Car* car)
{
    return car->carid;
}
/*void PrintCarList(ListNode* carlisthead)
{
    ListNode* aux;
    Car* auxcar;
    int count = 0;
    int i = 0;

    aux = carlisthead;

    while (aux != NULL)
    {
        count++;
        auxcar = (Car*) getItemLinkedList(aux);
        printf("Car %d: %s %d ", count, auxcar->carid, auxcar->status);
        printf("The path is: ");
        if (auxcar->path != NULL)
            for(i = 30; i != auxcar->path[i]; i = auxcar->path[i])
              printf("%d ", auxcar->path[i]);

        printf("\n");
        aux = getNextNodeLinkedList(aux);
    }
}*/


ListNode * RemoveCar(ListNode * carlisthead, Array decoder, int vertices, char * carname)
{
    ListNode * aux, * aux2, *prev;
    Event* auxevent;
    int i;

    aux = carlisthead;

    while(strcmp( GetCarID( getItemLinkedList(aux) ), carname ) != 0 )
    {
        prev = aux;
        aux = getNextNodeLinkedList(aux);
        /*Once we're out of this cicle we found the car we want to place in "the end" of the list*/
    }

   auxevent = (Event*)getItemLinkedList(aux);

   i = FindIP(vertices, GetEventCoord(auxevent, 'x'), GetEventCoord(auxevent, 'y'), GetEventCoord(auxevent, 'z'), decoder);

   FreePos(i, decoder, vertices); /*Removes the car from this parking slot with coords x,y,z */

   ( (Car *) getItemLinkedList(aux) )->status = 3; /* Marks the car as "left the parking lot"*/

   aux2 = aux; /*Start looking in the list from when we stoped on the last loop */
   while( GetCarStatus( getItemLinkedList(getNextNodeLinkedList(aux2)) ) != 3 )
        aux2 = getNextNodeLinkedList(aux2);

    if (carlisthead = aux)
        carlisthead = getNextNodeLinkedList(carlisthead); /*Removes aux from the list if it was the first element */
    else
        ModifyPointerNext(aux, getNextNodeLinkedList(aux)); /*Removes aux from the list if it was not the first element*/

    InsertNodeAfter(aux, aux2);
    return carlisthead;
}

ListNode* AddCar(ListNode * carlisthead, char * carname, int x, int y, int z, char objective, Array decoder, int vertices, Graph * graph, ListNode* accesseshead)
{
  Car * newcar;
  ListNode * aux;
  int i;
  int *st, *wt;

  st = (int*)malloc(sizeof(int)*vertices);
  VerifyMalloc((Item) st);
  wt = (int*)malloc(sizeof(int)*vertices);
  VerifyMalloc((Item) wt);



  newcar = (Car *) malloc( sizeof(Car) );
  VerifyMalloc((Item) newcar);


  /*Fill the car info*/
  newcar->carid = carname;
  newcar->status = 1;  /*means its an active car ~ not parked */
  newcar->carpath = ListInit(newcar->carpath);
  newcar->footpath = ListInit(newcar->footpath);

  i = FindIP(vertices, x, y, z, decoder);

  PathCalculator(graph, i, &(newcar->carpath), &(newcar->footpath), decoder, accesseshead, objective, vertices);

  PrintCarPath(newcar);

  carlisthead = AddNodeToListHead(carlisthead, (Item) newcar);

  return carlisthead;
}

void PrintCarPath(Car* car)
{
    printf("Car path: ");
    PrintIntList(car->carpath);
    printf("Foot Path: ");
    PrintIntList(car->footpath);
}
