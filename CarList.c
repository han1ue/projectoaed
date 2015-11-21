#include "Defs.h"

struct carstruct
{
    char * carid;
    int status;  /*status 1 means active car; status 2 means already parked car; status 3 means car already left the park*/
    Array path; /*Array that will contain the path from the entry to the access */
    int position; /*Index of the path array that the car is in right now */
};

Car* CarListInit(Event * eventlisthead, Array decoder, int vertices)
{
    Car * head, * new_car;
    ListNode* aux;
    Event* auxevent;
    
    if(eventlisthead == NULL)
    {
        printf("The event list is empty. There are no cars to add.");
        return NULL;
    }
    
    auxevent = eventlisthead;
    head = NULL;
    
    
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
            OccupyPos(GetEventCoord(auxevent, 'x'), GetEventCoord(auxevent, 'y'), GetEventCoord(auxevent, 'z'), decoder, vertices); /*This funcion will mark the spot (x,y,z) as occupied in the parking lot */
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

ListNode * RemoveCar(ListNode * carlisthead, Array decoder, int vertices, char * carname)
{
    int x, y, z;
    ListNode * aux, * aux2, *prev;
    
    aux = carlisthead;
    
    while(strcmp( GetCarID( getItemLinkedList(aux) ), carname ) != 0 )
    {
        prev = aux;
        aux = getNextNodeLinkedList(aux);
        /*Once we're out of this cicle we found the car we want to place in "the end" of the list*/
    }
    
    FreePos(x, y, z, decoder, vertices); /*Removes the car from this parking slot */
    
    ( (Car *) getItemLinkedList(aux) )->status = 3; /* Marks the car as "left the parking lot"*/
    
    aux2 = aux; /*Start looking in the list from when we stoped on the last loop */
    while( GetCarStatus( getItemLinkedList(getNextNodeLinkedList(aux2)) ) != 3 )
        aux2 = getNextNodeLinkedList(aux2);
    
    if (carlisthead = aux)
    {
        carlisthead = carlisthead->next;
        aux->next = aux2->next;
        aux2->next = aux;
        return carlisthead;
    }
    
    prev->next = aux->next;
    
    
    
    return carlisthead;
}
