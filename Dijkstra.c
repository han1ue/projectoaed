#include "Defs.h"

#define MAX_DISTANCE 10000

/******************************************************************************
 * Comparison
 *
 * Arguments: a, b  - two items that contain int* and we want to compare their ints
 *
 * Returns: 1 if a > b, 0 otherwise
 *
 *****************************************************************************/

int Comparison(Item a, Item b)
{
  int aa, bb;

  bb = *((int *) b);
  aa = *((int *) a);

  return (aa > bb);
}

void Dijsktra(Graph *G, int s, int* st, int* wt, int weight)
{
	int v, w, vertices, *newint;
  ListNode * t;
  Heap* heap;
  vertices = GetGraphVertices(G);
  heap = NewHeap(vertices, Comparison);

	for (v = 0; v < vertices; v++)
	{
  		 st[v] = -1;
  		 wt[v] = MAX_DISTANCE;

       newint =	(int*) malloc( sizeof(int) );
       *newint = v;
        HeapInit(heap, (Item) newint); //Se nao funcionar pode ser esta wannabe passagem por referencia
	}
  wt[s] = 0;
  FixUp(heap, s, wt);

  while (!HeapEmpty(heap))
  {
    v = *((int *)RemoveMin(heap, wt)); /*Removes the min value form the heap, returns it, and makes the array an heap again*/
    if (wt[v] != MAX_DISTANCE)
    {
      for (t = GetGraphAdjHead(G, v); t != NULL; getNextNodeLinkedList(t))
      {
       	w = *((int *)getItemLinkedList(t));
        if( wt[w] > wt[v] + weight)  /*If he's walking weight = 3; if he's on the car weight = 1;*/
        {
          wt[w] = wt[v] + weight;
          FixUp(heap, w, wt);
          st[w] = v;
        }
      }

    }
  }
}
