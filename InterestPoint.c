#include "Defs.h"

struct interestpoint
{
    /* coordinates of the vertice associated with this position in the array*/
    int x;
    int y;
    int z;
    /* type of vertice */
    char type;
  	/* flag - 1 if the position is restricted, 0 if not */
  	int flagres;
};

/******************************************************************************
 * GraphDecoderInit
 *
 * Arguments: matrix - number or elements in the graph
 *            col - number of collumns
 *            row - number of rows
 *            floors- number of floors
 *            vertices - number of vertices in the graph
 *
 * Returns: Pointer to array of pointers to InterestPoints. Each I.P. is related
 *          to a vertice in the graph and contains info about its place in the map
 *
 *****************************************************************************/
Array GraphDecoderInit(char *** matrix, int col, int row, int floors, int vertices)
{
    Array graphdecoder;
    InterestPoint* IP;

    int x, y, z, i = 0;


    graphdecoder = InitArray(vertices); /*Allocates memory for a vector of pointers to InterestPoints*/

    /* Goes through each point on the map, if it's not a wall, add it to the graph decoder*/
    for(z = 0; z < floors; z++)
    {
        for(y = 0; y < row; y++)
        {
            for(x = 0; x < col; x++)
            {
                if (matrix[x][y][z] != '@')
                {
                    IP =  (InterestPoint*) malloc( sizeof(InterestPoint) );
                    VerifyMalloc( (Item) IP );
                    /*Attributing values to the struct*/
                    IP->x = x;
                    IP->y = y;
                    IP->z = z;
                    IP->type = matrix[x][y][z];
                  	IP->flagres = 0;
                    /*Calls function that changes the item in the position i to the InterestPoint created above */
                    ModifyArrayNodeItem(i, (Item) IP, graphdecoder);
                    i++;
                }
            }
        }
    }

    return graphdecoder;
}



/******************************************************************************
 * GetIP_Coord
 *
 * Arguments: i - vertice from which we want to get the coordinate
 *						coord - coordinate we are looking for
 *						decoder - array that contains the vertices
 *
 * Returns: coordenate we wanted to get (x, y or z)
 *
 *****************************************************************************/

int GetIP_Coord(int i, char coord, Array decoder)
{
    InterestPoint * aux;
    aux = (InterestPoint *) GetArrayNodeItem(i, decoder);

    if(coord == 'x')
        return aux->x;
    else if(coord == 'y')
        return aux->y;
    else if(coord == 'z')
        return aux->z;
    else
    {
        printf("The coordenate you are trying to get does not exist.");
        exit(-1);
    }
}

/******************************************************************************
 * GetIP_Type
 *
 * Arguments: i - vertice from which we want to get the type
 *						decoder - array that contains the vertices
 *
 * Returns: type we wanted to get
 *
 *****************************************************************************/

char GetIP_Type(int i, Array decoder)
{
    InterestPoint * aux;
    aux = (InterestPoint *) GetArrayNodeItem(i, decoder);

    return aux->type;
}

/******************************************************************************
 * ChangeIP_Type
 *
 * Arguments: i - vertice from which we want to get the type
 *						decoder - array that contains the vertices
 *						type - type that we want to change the IP tp
 *
 * Returns: ---
 *
 *****************************************************************************/

void ChangeIP_Type(int i, Array decoder, char type)
{
  	InterestPoint * aux;
    aux = (InterestPoint *) GetArrayNodeItem(i, decoder);
  	aux->type = type;
}

/******************************************************************************
 * GetIP_FlagRes
 *
 * Arguments: i - vertice from which we want to get the flagres
 *						decoder - array that contains the vertices
 *
 * Returns: flagrestriction we want to get
 *
 *****************************************************************************/

int GetFlagRes(int i, Array decoder)
{
    InterestPoint * aux;
    aux = (InterestPoint *) GetArrayNodeItem(i, decoder);

    return aux->flagres;
}

/******************************************************************************
 * FindIP
 *
 * Arguments: x;y;z - coordinates of the vertice we want to find
 *						decoder - array that contains the vertices
 *
 * Returns: vertice of the IP with the coordinates entered in the arguments
 *
 *****************************************************************************/

int FindIP (int vertices, int x, int y, int z, Array decoder)
{
    int IP;

    for(IP = 0; IP < vertices; IP++)
    {
        if( GetIP_Coord(IP, 'x', decoder) == x && GetIP_Coord(IP, 'y', decoder) == y && GetIP_Coord(IP, 'z', decoder) == z )
        {
            return IP;
        }
    }

    if(IP == vertices)
    {
        printf("Error finding vertice with coordenates (x,y,z).");
        exit(-1);
    }
}

/******************************************************************************
 * OccupyPos
 *
 * Arguments: x;y;z - coordinates of the vertice we want to find
 *						decoder - array that contains the vertices
 *						vertices - nuber of vertices in the array
 *
 * Returns: occupies position with a parked car
 *
 *****************************************************************************/

void OccupyPos(int i, Array decoder, int vertices)
{
    InterestPoint * IP;

    IP = (InterestPoint*) decoder[i];
    IP->type = 'x';
}

/******************************************************************************
 * OccupyPos
 *
 * Arguments: x;y;z - coordinates of the vertice we want to find
 *						decoder - array that contains the vertices
 *						vertices - nuber of vertices in the array
 *
 * Returns: frees position because car left the building
 *
 *****************************************************************************/

void FreePos(int i, Array decoder, int vertices)
{
    InterestPoint * IP;

    IP = (InterestPoint*) decoder[i];
    IP->type = '.';
}

/******************************************************************************
 * RestrictPos
 *
 * Arguments: x;y;z - coordinates of the vertice we want to find
 *						decoder - array that contains the vertices
 *						vertices - nuber of vertices in the array
 *
 * Returns: adds a restriction to a point in the map
 *
 *****************************************************************************/

void RestrictPos(int i, Array decoder, int vertices)
{
    InterestPoint * IP;

    IP = (InterestPoint*) decoder[i];
    IP->flagres = 0;
}

/******************************************************************************
 * ReleasePos
 *
 * Arguments: x;y;z - coordinates of the vertice we want to find
 *						decoder - array that contains the vertices
 *						vertices - nuber of vertices in the array
 *
 * Returns: removes the restriction from a point in the map
 *
 *****************************************************************************/

void ReleasePos(int i, Array decoder, int vertices)
{
    InterestPoint * IP;

    IP = (InterestPoint*) decoder[i];
    IP->flagres = 1;
}

/******************************************************************************
 * HandleRestriction
 *
 * Arguments: auxevent - restriction event that we want to handle
 *						decoder - array that contains the vertices
 *						vertices - nuber of vertices in the array
 *
 * Returns: decides how to handle a restriction event
 *
 *****************************************************************************/

void HandleRestriction(Event * auxevent, Array decoder, int vertices)
{
  int x, y, z, flagres;
  int i;
  int counter = 0, floor;

  x = GetEventCoord(auxevent, 'x');
  y = GetEventCoord(auxevent, 'y');
  z = GetEventCoord(auxevent, 'z');

  if(y == -1) /*If its a floor restriction */
  {
    floor = GetIP_Coord(counter, 'z', decoder);
    while(floor <= z && counter < vertices) /*Stops once we finish restricting the floor or its the last vertice*/
    {
      floor = GetIP_Coord(counter, 'z', decoder);
      if(floor == z && GetIP_Type(counter, decoder) == '.') /*We only change the type of the parking spots becaus eits still possible to go by foot*/
      {
        ChangeIP_Type(counter, decoder, 'f'); /*Changes the type of this point on the map to f to show that is floor restricted*/
      }
      else if(floor == z && GetIP_Type(counter, decoder) == 'f') /*We want to "kill" the restriction and go back to regular parking*/
      {
        ChangeIP_Type(counter, decoder, '.'); /*Changes the type of this point on the map back to parking spot free from restrictions*/
      }
      counter++;
    }
  }
  else
  {
    i = FindIP(vertices, x, y, z, decoder);
    flagres = GetFlagRes(i, decoder);
  	if(flagres == 0) /*if its not already restricted then we have to restrict this pos*/
      RestrictPos(i, decoder, vertices);
    else
      ReleasePos(i, decoder, vertices); /*if it was restricted then we have to remove the restriction since its the second time it shows on the event list meaning its over*/
  }

}

ListNode * FindFreeSpots(Array decoder, int vertices)
{
  ListNode * freespots;
  int i;
  int * vertice;
  
  for(i = 0; i < vertices; i++)
  {
    if( GetIP_Type(i, decoder) == '.' )
    {
      	vertice = (int*) malloc ( sizeof(int) );
        freespots = AddNodeToListHead(freespots, (Item) vertice);
    }
  }
  
  return freespots;
}
