#include "Defs.h"

typedef struct adjacency Adjacency;

Array InitAdj(int, char ***, Array, int, int);
int GetAdjacencyWeight(Adjacency *);
int GetAdjacencyVertice(Adjacency *);
void freeAdj(Array, int);
