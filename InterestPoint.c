#include "Defs.h"

struct interestpoint
{
  /* coordinates of the vertice associated with this position in the array*/
  int x;
  int y;
  int z;
  /* type of vertice */
  char type;
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
 * FindIP
 *
 * Arguments: x;y;z - coordinates of the vertice we want to find
 *						decoder - array that contains the vertices
 *
 * Returns: vertice of the IP with the coordinates entered in the arguments
 *
 *****************************************************************************/

int * FindIP (int vertices, int x, int y, int z, Array decoder)
{
	int * IP, i;
  IP = NULL;

  for(i = 0; i < vertices; i++)
  {
    if( GetIP_Coord(i, 'x', decoder) == x && GetIP_Coord(i, 'y', decoder) == y && GetIP_Coord(i, 'z', decoder) == z )
    {
      IP = (int *) malloc( sizeof(int) );
      VerifyMalloc(IP);
      *IP = i;
  		return IP;
    }
  }

  if(IP == NULL)
  {
    printf("Error finding vertice with coordenates (x,y,z).");
  	exit(-1);
  }
}
