#include "Defs.h" /*Including here as well since we need to have access to this before and it only comes after in defs.h*/

struct eventstruct
{
    int time;
    char * carid;
    int x;
    int y;
    int z;
    char eventtype;
    char flag;
};

char* GetEventCar(Event* event)
{
    if ( event->eventtype != 'r' ) /* if the event is car related */
    {
        return event->carid;
    }
    else
    {
        printf("Error. You cant get a CarId from an event that is not car related.");
        exit (-1);
    }
}

int GetEventCoord(Event* event, char coord)
{
    if(coord == 'x')
        return event->x;
    else if(coord == 'y')
        return event->y;
    else if(coord == 'z')
        return event->z;
    else
    {
        printf("Error. You can only request x, y or z.");
        exit(-1);
    }
}



/******************************************************************************
 * EventListInit
 *
 * Arguments: carconfig - file pointer to the car cofig file
 *            resconfig - file pointer to the res config file
 *
 * Returns: Head of the event list
 *
 *****************************************************************************/
ListNode* EventListInit( FILE* carconfig, FILE* resconfig )
{
    char string[MAX_STRING];
    char carid[MAX_CAR_NAME];
    int time, x, y, z, varcounter, carnamelenght, tinit, tend;
    int i=0;
    char eventtype;
    ListNode* findcaraux, *head = NULL;
    Event * auxevent, * auxevent2, *findcarauxevent;

    /* Goes through every car event in the carconfig file */
    while( fgets(string, MAX_STRING, carconfig) != NULL)
    {

        /* Allocate memory for car related event */
        auxevent = (Event*) malloc( sizeof(Event) );
        VerifyMalloc( (Item) auxevent);

        /* Count number of read variables */
        varcounter = sscanf(string, "%s %d %c %d %d %d", carid, &time, &eventtype, &x, &y, &z);

        /* Discover lenght of car name so we can allocate memory for it */
        carnamelenght = strlen(carid);
        auxevent->carid = (char*) malloc( (carnamelenght + 1) * sizeof(char));
        VerifyMalloc( (Item) auxevent->carid);

        /* Add the name of the car to our structure */
        strcpy( (auxevent->carid), carid );
        /*Add the eventtype and the r(estriction)flag to the structure (the flag will only be used when the event its a restriction event) */
        auxevent->eventtype = eventtype;
        auxevent->time = time;

        if( varcounter == 3)            /*The event its an exit and the car was parked by Gestor */
        {
            findcaraux = head;
            while (findcaraux != NULL)
            {
            findcarauxevent = (Event*) getItemLinkedList(findcaraux);
            if(strcmp(carid, GetEventCar(findcarauxevent)) == 0)
                {
                     auxevent->x = GetEventCoord(findcarauxevent, 'x');
                     auxevent->y = GetEventCoord(findcarauxevent, 'y');
                     auxevent->z = GetEventCoord(findcarauxevent, 'z');
                     auxevent->flag = 'g';                                     /*This flag will tell us whether the car leaving was parked by gestor*/

                }
            findcaraux = getNextNodeLinkedList(findcaraux);
            }
        }
        else if( varcounter == 6) /*The event its a car arriving or The event its an exit and the car was already parked */
        {
            auxevent->x = x;
            auxevent->y = y;
            auxevent->z = z;
            auxevent->flag = '/';                /*This flag will tell us if the car was already parked*/
        }
        else
        {
            printf("Error. Confliting types or bad data format on car config file.");

            exit(-1);
        }

        head = insertSortedLinkedList(head, (Item) auxevent, CompareEventTime, 1); /* direction = 1 means ascending order */
    }

    /* Goes through every restriction event in the restriction file */
    while( fgets(string, MAX_STRING, resconfig) != NULL)
    {
        /* Allocate memory for two restricton related events */
        auxevent = (Event*) malloc( sizeof(Event) );    /* auxevent  --> event that "creates (ta)" the restriction*/
        VerifyMalloc( (Item) auxevent);
        auxevent2 = (Event*) malloc( sizeof(Event) ); /*auxevent2 --> event that "destroys (tb)" the restriction */
        VerifyMalloc( (Item) auxevent2);

        /* Count number of read variables */
        varcounter = sscanf(string, "%*c %d %d %d %d %d", &tinit, &tend, &x, &y, &z);

        auxevent->eventtype = 'r';  /*convention for a restriction event type is 'r'*/
        auxevent2->eventtype = 'r';
        auxevent->carid = NULL;         /*carid string has no meaning in restriction related events*/
        auxevent2->carid = NULL;

        if( varcounter == 3 )
        {
            auxevent->time = tinit;     /* auxevent  --> event that "creates" the restriction*/
            auxevent->x = -1;
            auxevent->y = -1;
            auxevent->z = x;				/*the x value (in this case) represents the floor that's gonna be restricted and we're saving it in the coord z so its more intuitive in the future*/
            auxevent->flag = 'f';     /* f flag means floor, for a whole floor event*/

            if ( tend != 0) /*If the restriction is endless then we dont need to add the "ending event" to the list */
            {
                auxevent2->time = tend;
                auxevent2->x = -1;
                auxevent2->y = -1;
                auxevent2->z = x;
                auxevent2->flag = 'f';
            }
        }
        else if( varcounter == 5 )
        {
            auxevent->time = tinit;     /* auxevent  --> event that "creates" the restriction*/
            auxevent->x = x;                    /*the x value (in this case) represents the floor that's gonna be restricted*/
            auxevent->y = y;
            auxevent->z = z;
            auxevent->flag = 'p';      /* p flag means position for a position related event*/

            if ( tend != 0) /*If the restriction is endless then we dont need to add the "ending event" to the list */
            {
                auxevent2->time = tend;
                auxevent2->x = x;
                auxevent2->y = y;
                auxevent2->z = z;
                auxevent2->flag = 'p';
            }
        }

        else
        {
            printf("Error. Confliting types or bad data format on car config file.");
            exit(-1);
        }

        head = insertSortedLinkedList(head, (Item) auxevent, CompareEventTime, 1);

        if ( tend != 0)
            head = insertSortedLinkedList(head, (Item) auxevent2, CompareEventTime, 1);
    }

    return head;
}

/******************************************************************************
 * GetEventTime
 *
 * Arguments: event - event we want to get the time from
 *
 *
 * Returns: time of the chosen event
 *
 *****************************************************************************/

int GetEventTime(Event *event)
{
    return event->time;
}

/******************************************************************************
 * CompareEventTime
 *
 * Arguments: event1/event2 - events we want to compare the time from
 *
 * Comments: direction 1 = ascending order; direction 2 = descending order
 *
 * Returns: 1 if event1->time >= event2->time and 0 otherwise
 *
 *****************************************************************************/

int CompareEventTime(Item event1, Item event2, int direction)
{
    int r;

    if (direction == 1)
    {
        if (GetEventTime((Event*) event1) > GetEventTime((Event*) event2))
            r = 1 ;
        else
            r = 0;
    }
    else if (direction == 2)
    {
        if (GetEventTime((Event*) event1) > GetEventTime((Event*) event2))
            r = 0 ;
        else
            r = 1;
    }
    return r;
}

char GetEventType(Event* event)
{
    return event->eventtype;
}

char GetEventFlag(Event* event)
{
    return event->flag;
}


void PrintEventList(ListNode* eventlisthead)
{
    ListNode* aux;
    Event* auxevent;
    int count = 0;

    aux = eventlisthead;

    while (aux != NULL)
    {
        count++;
        auxevent = (Event*) getItemLinkedList(aux);
        printf("Event %d: %d %s %d %d %d %c %c\n", count, auxevent->time, auxevent->carid, auxevent->x, auxevent->y, auxevent->z, auxevent->eventtype, auxevent->flag);
        aux = getNextNodeLinkedList(aux);
    }
}

ListNode* ExecuteEvent( ListNode *eventlisthead, ListNode **carlisthead, int timeunit, ParkingLot * parkinglot)
{

    ListNode * aux, *prev;
    Event* auxevent;
    char type;
    Array decoder = GetDecoder(parkinglot);
    int vertices = GetVertices(parkinglot);
    ListNode * accesseshead = GetAccesses(parkinglot);
    Graph * graph = GetGraph(parkinglot);
    int freespots = GetFreeSpots(parkinglot);

    aux = eventlisthead;

    if(aux == NULL)
        return;

    auxevent = (Event*) getItemLinkedList(aux);

    while( aux != NULL && (GetEventTime(auxevent) <= timeunit) )
    {
        type = GetEventType(auxevent);

        if (type == 'S') /*If the vent type its an exit from the parking lot*/
        {
            *carlisthead = RemoveCar(graph, *carlisthead, accesseshead, decoder, vertices, GetEventCar(auxevent));
            IncFreeSpots(parkinglot);
        }

        else if (type == 'r') /* If the event its a restriction */
          *carlisthead = HandleRestriction(graph, accesseshead, auxevent, decoder, *carlisthead, vertices, parkinglot);

        else
        {
          *carlisthead = AddCar(*carlisthead, GetEventCar(auxevent), GetEventCoord(auxevent, 'x'), GetEventCoord(auxevent, 'y') ,GetEventCoord(auxevent, 'z'), type, decoder, vertices, graph, accesseshead, freespots);
          DecFreeSpots(parkinglot);
        }

        prev = aux;
        aux = getNextNodeLinkedList(aux);
        auxevent = (Event*) getItemLinkedList(aux);
        free(prev); /*Frees event from the list after it was processed */
    }

    return aux;

}
