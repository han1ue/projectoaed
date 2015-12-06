#include "Defs.h" /*Including here as well since we need to have access to this before and it only comes after in defs.h*/

struct reststruct
{
    int time;
    int x;
    int y;
    int z;
    char flag;
};

ListNode* RestInit( FILE* restfile)
{

    char string[MAX_STRING];
    int x, y, z, varcounter, tinit, tend;
    ListNode *head = NULL;
    Rest * auxrest, * auxrest2;
      /* Goes through every restriction rest in the restriction file */
    while( fgets(string, MAX_STRING, restfile) != NULL)
    {
        /* Allocate memory for two restricton related rests */
        auxrest = (Rest*) malloc( sizeof(Rest) );    /* auxrest  --> rest that "creates (ta)" the restriction*/
        VerifyMalloc( (Item) auxrest);
        auxrest2 = (Rest*) malloc( sizeof(Rest) ); /*auxrest2 --> rest that "destroys (tb)" the restriction */
        VerifyMalloc( (Item) auxrest2);

        /* Count number of read variables */
        varcounter = sscanf(string, "%*c %d %d %d %d %d", &tinit, &tend, &x, &y, &z);

        if( varcounter == 3 )
        {
            auxrest->time = tinit;     /* auxrest  --> rest that "creates" the restriction*/
            auxrest->x = -1;
            auxrest->y = -1;
            auxrest->z = x;				/*the x value (in this case) represents the floor that's gonna be restricted and we're saving it in the coord z so its more intuitive in the future*/
            auxrest->flag = 'f';     /* f flag means floor, for a whole floor rest*/

            if ( tend != 0) /*If the restriction is endless then we dont need to add the "ending rest" to the list */
            {
                auxrest2->time = tend;
                auxrest2->x = -1;
                auxrest2->y = -1;
                auxrest2->z = x;
                auxrest2->flag = 'f';
            }
        }
        else if( varcounter == 5 )
        {
            auxrest->time = tinit;     /* auxrest  --> rest that "creates" the restriction*/
            auxrest->x = x;                    /*the x value (in this case) represents the floor that's gonna be restricted*/
            auxrest->y = y;
            auxrest->z = z;
            auxrest->flag = 'p';      /* p flag means position for a position related rest*/

            if ( tend != 0) /*If the restriction is endless then we dont need to add the "ending rest" to the list */
            {
                auxrest2->time = tend;
                auxrest2->x = x;
                auxrest2->y = y;
                auxrest2->z = z;
                auxrest2->flag = 'p';
            }
        }

        else
        {
            printf("Error. Confliting types or bad data format on rest config file.");
            exit(0);
        }

        head = insertSortedLinkedList(head, (Item) auxrest, CompareRestTime, 1);

        if ( tend != 0)
            head = insertSortedLinkedList(head, (Item) auxrest, CompareRestTime, 1);
    }

    return head;
}

/******************************************************************************
 * GetRestTime
 *
 * Arguments: Rest - Rest we want to get the time from
 *
 *
 * Returns: time of the chosen Rest
 *
 *****************************************************************************/

int GetRestTime(Rest *Rest)
{
    return Rest->time;
}

/******************************************************************************
 * CompareRestTime
 *
 * Arguments: Rest1/Rest2 - Rests we want to compare the time from
 *
 * Comments: direction 1 = ascending order; direction 2 = descending order
 *
 * Returns: 1 if Rest1->time >= Rest2->time and 0 otherwise
 *
 *****************************************************************************/

int CompareRestTime(Item Rest1, Item Rest2, int direction)
{
    int r=0;

    if (direction == 1)
    {
        if (GetRestTime((Rest*) Rest1) > GetRestTime((Rest*) Rest2))
            r = 1 ;
        else
            r = 0;
    }
    else if (direction == 2)
    {
        if (GetRestTime((Rest*) Rest1) > GetRestTime((Rest*) Rest2))
            r = 0 ;
        else
            r = 1;
    }
    return r;
}


/******************************************************************************
 * HandleRest
 *
 * Arguments:
 *
 *
 * Returns:
 *
 *****************************************************************************/

ListNode * HandleRest(ListNode * resthead, ParkingLot * parkinglot, int timeunit, FILE * outputfile)
{
      Rest * rest;
      ListNode * aux;
      int i=0;
      /*Get the head of the restricion list to the aux pointer for the first while comparation*/
      aux = resthead;

      if(aux == NULL)
        return NULL;

      /*Get the first restriction*/
      rest = (Rest*) getItemLinkedList(aux);

      while(aux != NULL && GetRestTime(rest) == timeunit)
      {
          if(GetRestFlag(rest) == 'p')
          {
            i = FindIP(GetVertices(parkinglot), GetRestCoord(rest, 'x'), GetRestCoord(rest, 'y'), GetRestCoord(rest, 'z'), GetDecoder(parkinglot) );

            if(GetIP_Flagres(i, GetDecoder(parkinglot) ) == 1)
             {
                 ReleasePos(i, GetDecoder(parkinglot) );
                 IncFreeSpots(parkinglot);
                if( GetFreeSpots(parkinglot) != 0)
                  HandleQueue(parkinglot, outputfile, timeunit);
              }
            else
            {
                RestrictPos(i, GetDecoder(parkinglot) );
                DecFreeSpots(parkinglot);
            }
          }
          else if(GetRestFlag(rest) == 'f')
          {
            if( IsFloorRestricted( GetRestCoord(rest, 'z'), parkinglot ) )
            {
            	ReleaseWholeFloor(i, parkinglot ); /* la dento temos de fazer bue release spots */
              if( GetFreeSpots(parkinglot) != 0)
           			HandleQueue(parkinglot, outputfile, timeunit);
            }
            else
              RestrictWholeFloor( GetRestCoord(rest, 'z'), parkinglot );
          }


        aux = getNextNodeLinkedList(aux);
        rest = (Rest*) getItemLinkedList(aux);
      }

      /*Return the new head of the linked list*/
      return aux;

}


char GetRestFlag(Rest* rest)
{
    return rest->flag;
}

int GetRestCoord(Rest* rest, char coord)
{
    if(coord == 'x')
        return rest->x;
    else if(coord == 'y')
        return rest->y;
    else if(coord == 'z')
        return rest->z;
    else
    {
        printf("Error. You can only request x, y or z.");
        exit(0);
    }
}

int IsFloorRestricted( int z, ParkingLot * parkinglot)
{
  int i;
  int vertices = GetVertices(parkinglot);

  for(i = 0; (i < vertices) && (GetIP_Coord(i, 'z', GetDecoder(parkinglot) ) <= z) ; i++)
  {
    if( (GetIP_Coord(i, 'z', GetDecoder(parkinglot)) == z) && (GetIP_Flagres(i, GetDecoder(parkinglot)) == 0) && (GetIP_Type(i, GetDecoder(parkinglot)) == '.') )
       return 0;
  }

    return 1;
}

void ReleaseWholeFloor( int z, ParkingLot * parkinglot )
{
  int i;
  int vertices = GetVertices(parkinglot);

  for(i = 0; (i < vertices) && (GetIP_Coord(i, 'z', GetDecoder(parkinglot) ) <= z) ; i++)
  {
    if( (GetIP_Coord(i, 'z', GetDecoder(parkinglot)) == z) && (GetIP_Flagres(i, GetDecoder(parkinglot)) == 1) && (GetIP_Type(i, GetDecoder(parkinglot)) == '.' ))
    {
      ReleasePos(i, GetDecoder(parkinglot) );
      IncFreeSpots(parkinglot);
    }
  }
}
void RestrictWholeFloor( int z, ParkingLot * parkinglot )
{
  int i;
  int vertices = GetVertices(parkinglot);

  for(i = 0; (i < vertices) && (GetIP_Coord(i, 'z', GetDecoder(parkinglot) ) <= z) ; i++)
  {
    if( (GetIP_Coord(i, 'z', GetDecoder(parkinglot)) == z) && (GetIP_Flagres(i, GetDecoder(parkinglot)) == 0) && (GetIP_Type(i, GetDecoder(parkinglot)) == '.' ))
    {
      RestrictPos(i, GetDecoder(parkinglot) );
      DecFreeSpots(parkinglot);
    }
  }
}
