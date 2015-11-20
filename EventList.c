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
  int time, x, y, z, varcounter, carnamelenght;
  int i=0;
  char eventtype;
  ListNode* head = NULL;
  Event * auxevent;
  
  /* Goes through every car event in the carconfig file */
  while( fgets(string, MAX_STRING, carconfig) != EOF)
  {
    
    /* Allocate memory for robot name */
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
    auxevent->rflag = -1;
                                     
  	if( varcounter == 3)			/*The event its an exit and the car was parked by Gestor */
    {
      auxevent->x = -1;
      auxevent->y = -1;
      auxevent->z = -1;
    }
    else if( varcounter == 5 ) /*The event its a car arriving or The event its an exit and the car was already parked */
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
