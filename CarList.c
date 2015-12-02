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
            new_car->status = 1;
            new_car->carpath = ListInit(new_car->carpath);
            new_car->footpath = ListInit(new_car->footpath);
            head = AddNodeToListHead(head, (Item) new_car);
          	i = FindIP(vertices, GetEventCoord(auxevent, 'x'), GetEventCoord(auxevent, 'y'), GetEventCoord(auxevent, 'z'), decoder);
            OccupyPos(i, decoder, vertices); /*This funcion will mark the spot (x,y,z) as occupied in the parking lot */
            DecFreeSpots(parkinglot);
        }
        aux = getNextNodeLinkedList(aux);
    }

    return head;
}


int GetCarStatus(Car* car)
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
    return (car->carid);
}
void PrintCarList(ListNode* carlisthead)
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
        printf("Car %d: %s %d \n", count, auxcar->carid, auxcar->status);
        aux = getNextNodeLinkedList(aux);
    }
}

ListNode * HandleQueue(Graph * graph, Array decoder, ListNode * accesseshead, ListNode * carlisthead, int vertices, int * queueflag)
{
  ListNode *aux, *objectivenode, *aux2;
  Car * car;
  char * objective;
  int * source;

  car = (Car *) getItemLinkedList(carlisthead);

  source = (int *) getItemLinkedList(car->carpath);

  objectivenode = getNextNodeLinkedList(car->carpath);

  objective = (char *) getItemLinkedList(objectivenode);

  if( car->status != 0)
  {
    *queueflag = 1;
    return carlisthead;
  }

  car->status = 1;
  PathCalculator(graph, *source, &(car->carpath), &(car->footpath), decoder, accesseshead, *objective, vertices);

  /* Make the queded car leave the queue */

  aux = carlisthead;
  aux2 = carlisthead;

  while( getNextNodeLinkedList(aux2) != NULL && ( GetCarStatus( (Car *) getItemLinkedList( getNextNodeLinkedList(aux2) ) ) != 1 ))
    aux2 = getNextNodeLinkedList(aux2);

  if( aux2 != carlisthead)
  {
    carlisthead = getNextNodeLinkedList(carlisthead);
    InsertNodeAfter(aux, aux2);
  }

    printf("Remove car from queue \n");
    PrintCarList(carlisthead);

  /* Free the memory used to bring the variables in*/

  free(objectivenode);
  free(objective);
  free(source);

  return carlisthead;
}



ListNode * RemoveCar(Graph * graph, ListNode * carlisthead, ListNode * accesseshead, Array decoder, int vertices, Event* auxevent, int * queueflag)
{
    ListNode * aux, * aux2, *prev;
    int i;
    char * carname;

    carname = GetEventCar(auxevent);

    aux = carlisthead;

    while(strcmp( GetCarID( (Car*) getItemLinkedList(aux) ), carname ) != 0 )
    {
        prev = aux;
        aux = getNextNodeLinkedList(aux);
        /*Once we're out of this cicle we found the car we want to place in "the end" of the list*/
    }

   i = FindIP(vertices, GetEventCoord(auxevent, 'x'), GetEventCoord(auxevent, 'y'), GetEventCoord(auxevent, 'z'), decoder);

   FreePos(i, decoder, vertices); /*Removes the car from this parking slot with coords x,y,z */

   ( (Car *) getItemLinkedList(aux) )->status = 2; /* Marks the car as "left the parking lot"*/

   aux2 = aux; /*Start looking in the list from when we stoped on the last loop */

    if(getNextNodeLinkedList(aux) != NULL)
    {
       while( getNextNodeLinkedList(aux2) != NULL && ( GetCarStatus( (Car*) getItemLinkedList(getNextNodeLinkedList(aux2)) ) != 2 ) )
            aux2 = getNextNodeLinkedList(aux2);

        if (carlisthead == aux)
            carlisthead = getNextNodeLinkedList(carlisthead); /*Removes aux from the list if it was the first element */
        else
            ModifyPointerNext(prev, getNextNodeLinkedList(aux)); /*Removes aux from the list if it was not the first element*/

        InsertNodeAfter(aux, aux2);
    }

    printf("Before handling queue and after removing \n");
    PrintCarList(carlisthead);

  	carlisthead = HandleQueue(graph, decoder, accesseshead, carlisthead, vertices, queueflag);

    return carlisthead;
}

ListNode* AddCar(ListNode * carlisthead, char * carname, int x, int y, int z, char objective, Array decoder, int vertices, Graph * graph, ListNode* accesseshead, int freespots)
{
  Car * newcar;
  char * queueobjective;
  int * queuesource;
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

  newcar->carpath = ListInit(newcar->carpath);
  newcar->footpath = ListInit(newcar->footpath);
  i = FindIP(vertices, x, y, z, decoder);

  if(freespots != 0)
  {
    newcar->status = 1;  /*means its an active car ~ already processed */
    PathCalculator(graph, i, &(newcar->carpath), &(newcar->footpath), decoder, accesseshead, objective, vertices);
    //PrintCarPath(newcar);
    printf("Add Normal Car \n\n");
    printf("FreeSpots: %d\n\n", freespots);
	}
  else
  {
  	newcar->status = 0;  /*means its an queded car ~ not processed yet */

    /*Using the carpath LinkedList as a support list to save the source and objective of a queued car */
    queueobjective = (char*) malloc( sizeof(char) );
    VerifyMalloc( (Item) queueobjective);

    *queueobjective = objective;

    newcar->carpath = AddNodeToListHead(newcar->carpath, (Item) queueobjective);

    queuesource = (int*) malloc( sizeof(int) );
    VerifyMalloc( (Item) queuesource);

    *queuesource = i;

    newcar->carpath = AddNodeToListHead(newcar->carpath, (Item) queuesource);

    printf("Add Queue Car \n");
  }

  carlisthead = insertSortedLinkedList(carlisthead, (Item) newcar, CompareCarStatus, 1); //esta direction pode tar errada, confirmar se necessario
  PrintCarList(carlisthead);
  return carlisthead;
}


void PrintCarPath(Car* car)
{
    printf("Car path: ");
    PrintIntList(car->carpath);
    printf("Foot Path: ");
    PrintIntList(car->footpath);
}
