#include "Defs.h"

struct eventstruct
{
    int time;
    char * carid;
    int x;
    int y;
    int z;
    char eventtype;
    char rflag;
};


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
    ListNode* head = NULL;
    Event * auxevent, * auxevent2;

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
        auxevent->rflag = '/';
        auxevent->time = time;

        if( varcounter == 3)			/*The event its an exit and the car was parked by Gestor */
        {
            auxevent->x = -1;
            auxevent->y = -1;
            auxevent->z = -1;
        }
        else if( varcounter == 6) /*The event its a car arriving or The event its an exit and the car was already parked */
        {
            auxevent->x = x;
            auxevent->y	= y;
            auxevent->z = z;
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
        auxevent = (Event*) malloc( sizeof(Event) );	/* auxevent  --> event that "creates (ta)" the restriction*/
        VerifyMalloc( (Item) auxevent);
        auxevent2 = (Event*) malloc( sizeof(Event) ); /*auxevent2 --> event that "destroys (tb)" the restriction */
        VerifyMalloc( (Item) auxevent2);

        /* Count number of read variables */
        varcounter = sscanf(string, "%*c %d %d %d %d %d", &tinit, &tend, &x, &y, &z);

        auxevent->eventtype = 'r'; 	/*convention for a restriction event type is 'r'*/
        auxevent2->eventtype = 'r';
        auxevent->carid = NULL; 		/*carid string has no meaning in restriction related events*/
        auxevent2->carid = NULL;

        if( varcounter == 3 )
        {
            auxevent->time = tinit;     /* auxevent  --> event that "creates" the restriction*/
            auxevent2->time = tend;
            auxevent->x = x;    				/*the x value (in this case) represents the floor that's gonna be restricted*/
            auxevent2->x = x;
            auxevent->y = -1;
            auxevent2->y = -1;
            auxevent->z = -1;
            auxevent2->z = -1;
            auxevent->rflag = 'f';     /* f flag means floor, for a whole floor event*/
            auxevent2->rflag = 'f';
        }
        else if( varcounter == 5 )
        {
            auxevent->time = tinit;     /* auxevent  --> event that "creates" the restriction*/
            auxevent2->time = tend;
            auxevent->x = x;    				/*the x value (in this case) represents the floor that's gonna be restricted*/
            auxevent2->x = x;
            auxevent->y = y;
            auxevent2->y = y;
            auxevent->z = y;
            auxevent2->z = y;
            auxevent->rflag = 'p';     	/* p flag means position for a position related event*/
            auxevent2->rflag = 'p';
        }

        else
        {
            printf("Error. Confliting types or bad data format on car config file.");
            exit(-1);
        }

        head = insertSortedLinkedList(head, (Item) auxevent, CompareEventTime, 1);
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
        printf("Event %d: %d %s %d %d %d %c %c\n", count, auxevent->time, auxevent->carid, auxevent->x, auxevent->y, auxevent->z, auxevent->eventtype, auxevent->rflag);
        aux = getNextNodeLinkedList(aux);
    }
}

/*ListNode* ExecuteEvent( ListNode *eventlisthead, ListNode **carlisthead, int timeunit, Array decoder, int vertices)
{

    ListNode * aux, *prev;
    Event* auxevent;
    char type;

    aux = eventlisthead;

    if(aux == NULL)
        return;

    auxevent = (Event*) getItemLinkedList(aux);
    while( aux != NULL && (GetEventTime(auxevent) < timeunit) )
    {
        auxevent = (Event*) getItemLinkedList(aux);
        type = GetEventType(auxevent);

        if (type == 'S')
        {

            *carlisthead = RemoveCar(*carlisthead, decoder, vertices, GetEventCar(auxevent));

            mudar status, alterar pos na lista  -> precisa do decoder e da lista de carros
                }

        prev = aux;
        aux = getNextNodeLinkedList(aux);
        free(prev);	/*Frees event from the list after it was processed */
 //   }

  //  return aux;

//}
