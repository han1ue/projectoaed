#include "Defs.h"

struct carstruct
{
  char * carid;
  int status;  /*status 1 means active car; status 2 means already parked car; status 3 means car already left the park*/
  Array path; /*Array that will contain the path from the entry to the access */
  int position; /*Index of the path array that the cr is in right now */
};

Car* CarListInit(Event * eventlisthead)
  {
    Car * head, * new_car;
    ListNode* aux;
    Event* auxevent;

    if(eventlisthead == NULL)
    {
        printf("The event list is empty. There are no cars to add.");
        return NULL;
    }

    head = NULL;
    aux = eventlisthead;


    while (aux != NULL)
    {
        auxevent = (Event*) getItemLinkedList(aux);
        if(GetEventType(auxevent) == 'S' && GetEventCoord(auxevent, 'x') != -1) /*Puts the cars already parked in the car array */
        {
            new_car = (Car*) malloc( sizeof(Car) );
            strcpy((new_car->carid),GetEventCar(auxevent));
            new_car->status = 2;
            new_car->path = NULL;
            new_car->position = 0;
            head = AddNodeToListHead(head, (Item) new_car);
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


void PrintCarList(ListNode* carlisthead)
{
    ListNode* aux;
    Car* auxcar;
    int count = 0;

    aux = carlisthead;

    while (aux != NULL)
    {
        count++;
        auxcar = (Car*) getItemLinkedList(aux);
        printf("Car %d: %s %d %d\n", count, auxcar->carid, auxcar->status, auxcar->position);
        aux = getNextNodeLinkedList(aux);
    }
}

