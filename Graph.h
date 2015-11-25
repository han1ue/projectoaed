#include "Defs.h"

typedef struct graph Graph;

Graph *GraphInit(int, char***, Array, int, int, int);
void PrintGraph(Graph*, int);
int GetGraphVertices(Graph *);
LinkedList* GetGraphAdjHead(Graph *, int);
