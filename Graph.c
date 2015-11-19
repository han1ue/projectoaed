#include "Defs.h"

struct graph
{
  int v;
  int e;
  Array adj;
};

/******************************************************************************
 * GraphInit
 *
 * Arguments: vertices - number of vert in the graph
 *						matrix - 3d map of the parkinglot
 *        		decoder - aux array that contains info about the vertices
 * Returns: pointer to the created graph
 *
 *****************************************************************************/

Graph *GraphInit(int vertices, char *** matrix, Array decoder, int col, int row, int floors)
{
 Graph *G = (Graph*) malloc( sizeof(Graph) ); /*antes estava sizeof(struct graph)*/
 VerifyMalloc( (Item) G );
 G->v = vertices;
 G->e = 0;
 G->adj = InitAdj(vertices, matrix, decoder, col, row, floors);
 return G;
}
