#include "Defs.h"

struct carstruct
{
    char * carid;
    int time;
    char type;
    int x;
    int y;
    int z;

};

int HandleCar(ParkingLot* parkinglot, FILE* carfile, FILE* outputfile, int timeunit)
{
    static Car* newcar = NULL;
    char carname[5];
    char string[MAX_STRING];
    int pathweight, finalflag = 0;
    ListNode *carpath = ListInit();
    ListNode *footpath = ListInit();

    if(newcar == NULL) /*Inicializes the ponter ONLY in the first time we enter this function */
    {
        newcar = (Car*)malloc(sizeof(Car));
        fgets(string, MAX_STRING, carfile);
        if ( sscanf(string, "%s %d %c %d %d %d ", carname, &(newcar->time), &(newcar->type), &(newcar->x), &(newcar->y), &(newcar->z)) != 6)
        {
             newcar->x = -1;
             newcar->y = -1;
             newcar->z = -1;
        }

        newcar->carid = (char*) malloc(sizeof(char) * ( strlen(carname) + 1 ) );

        strcpy(newcar->carid, carname );
    }

    while(newcar->time == timeunit) /*We have to process the car we have right now and then get a new car*/
    {
        if (newcar->type != 'S')
        {

            escreve_saida(outputfile, newcar->carid, newcar->time, newcar->x, newcar->y, newcar->z, 'i'); /*Writes the entrance of the first car*/

            if(GetFreeSpots(parkinglot) != 0)
            {

                pathweight = PathCalculator(GetGraph(parkinglot), FindIP(GetVertices(parkinglot), newcar->x, newcar->y, newcar->z, GetDecoder(parkinglot)), &carpath, &footpath, GetDecoder(parkinglot), GetAccesses(parkinglot), newcar->type, GetVertices(parkinglot));


                PrintPath(outputfile, carpath, footpath, newcar->carid, newcar->time, parkinglot, pathweight);

                GetParkedCarCoords(parkinglot, newcar->carid, &(newcar->x), &(newcar->y), &(newcar->z));/*Gets the coordinates where gestor parked the car with this carid */
                OccupyPos(FindIP(GetVertices(parkinglot), newcar->x, newcar->y, newcar->z, GetDecoder(parkinglot)),GetDecoder(parkinglot), GetVertices(parkinglot));
                DecFreeSpots(parkinglot);

                //falta fazer o resumo aka cena com "x"
            }
            else
            {
                InsertinQueue(parkinglot, newcar);
                PrintQueueCars(parkinglot);
            }
        }
        else
        {
            if (newcar->x != -1)
                escreve_saida(outputfile, newcar->carid, newcar->time, newcar->x, newcar->y, newcar->z, 's');
            else
            {
                GetParkedCarCoords(parkinglot, newcar->carid, &(newcar->x), &(newcar->y), &(newcar->z));
                escreve_saida(outputfile, newcar->carid, newcar->time, newcar->x, newcar->y, newcar->z, 's');
            }
            IncFreeSpots(parkinglot);
            FreePos(FindIP(GetVertices(parkinglot), newcar->x, newcar->y, newcar->z, GetDecoder(parkinglot)),GetDecoder(parkinglot), GetVertices(parkinglot));
            HandleQueue(parkinglot, outputfile, newcar->time);
            //tratar da saída - libertar a said, imprimir  saida e handle aueue
        }

        if (fgets(string, MAX_STRING, carfile) == NULL) /* Get a new car from the file */
        {
            finalflag = 1;
            break;  /*If we are reading a car after the last one */
        }
        if ( sscanf(string, "%s %d %c %d %d %d ", carname, &(newcar->time), &(newcar->type), &(newcar->x), &(newcar->y), &(newcar->z)) != 6)
        {
             newcar->x = -1;
             newcar->y = -1;
             newcar->z = -1;
        }
        strcpy(newcar->carid, carname);
    }


    return finalflag;
}

void InsertinQueue(ParkingLot * parkinglot, Car * newcar)
{
    Car* queuedcar = (Car*)malloc(sizeof(Car));

    queuedcar->carid = (char*) malloc( sizeof(char) * ( strlen(newcar->carid) + 1 ) );
    strcpy(queuedcar->carid, newcar->carid);
    queuedcar->time = newcar->time;
    queuedcar->type = newcar->type;
    queuedcar->x = newcar->x;
    queuedcar->y = newcar->y;
    queuedcar->z = newcar->z;

	if( GetQueueHead(parkinglot) == NULL)
        SetQueueHead(parkinglot, AddNodeToListHead( GetQueueHead(parkinglot), (Item) queuedcar) );
    else
        AddNodeToTail(GetQueueHead(parkinglot), (Item) queuedcar);
}

void HandleQueue(ParkingLot * parkinglot, FILE* outputfile, int time)
{
  ListNode * queuehead = GetQueueHead(parkinglot);
  ListNode* carpath = ListInit();
  ListNode* footpath = ListInit();
  Car* queuecar;
  int pathweight;

  if(queuehead == NULL)
    return;
  else
  {

    queuecar = (Car*) getItemLinkedList(queuehead);

    pathweight = PathCalculator(GetGraph(parkinglot), FindIP(GetVertices(parkinglot), queuecar->x, queuecar->y, queuecar->z, GetDecoder(parkinglot)), &carpath, &footpath, GetDecoder(parkinglot), GetAccesses(parkinglot), queuecar->type, GetVertices(parkinglot));
    PrintPath(outputfile, carpath, footpath, queuecar->carid, time, parkinglot, pathweight);
    SetQueueHead(parkinglot, RemoveListHead(queuehead) );
    DecFreeSpots(parkinglot);
  }
}

void PrintQueueCars(ParkingLot * parkinglot)
{
    ListNode * queuecarhead = GetQueueHead(parkinglot);
    ListNode * aux;
    Car * queuecar;

    for(aux = queuecarhead; aux != NULL; aux = getNextNodeLinkedList(aux) )
    {
        queuecar = (Car*) getItemLinkedList(aux);

        printf("%s %d %c %d %d %d\n", queuecar->carid, queuecar->time, queuecar->type, queuecar->x, queuecar->y, queuecar->z);
    }
}

