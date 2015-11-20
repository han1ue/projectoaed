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
NodeList* EventListInit( FILE* carconfig, FILE* resconfig )
{
    char string[MAX_STRING];
    char carid[MAX_CAR_NAME];
    int time, x, y, z, varcounter, carnamelenght, tinit, tend;
    int i=0;
    char eventtype;
    ListNode* head = NULL;
    Event * auxevent, * auxevent2;
    
    /* Goes through every car event in the carconfig file */
    while( fgets(string, MAX_STRING, carconfig) != EOF)
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
        
        insertSortedLinkedList(head, (Item) auxevent);
    }
    
    /* Goes through every restriction event in the restriction file */
    while( fgets(string, MAX_STRING, resconfig) != EOF)
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
        
        insertSortedLinkedList(head, (Item) auxevent);
        insertSortedLinkedList(head, (Item) auxevent2);
        
    }
    
    return head;
}

/******************************************************************************
 * GetEventTime
 *
 * Arguments: carconfig - file pointer to the car cofig file
 *            
 *        
 * Returns: time of the chosen event
 *
 *****************************************************************************/

int GetEventTime(Event *event)
{
    int time;
    return event->time;
}