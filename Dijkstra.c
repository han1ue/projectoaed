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



void Dijsktra(Graph *G, int s, int* st, int* wt, int weight_mult_factor, Array decoder)
{
    int v, w, vertices, *newint, weight, n_elements, aux;
    ListNode * t;
    Heap* heap;
    vertices = GetGraphVertices(G);
    heap = NewHeap(vertices, Comparison);
    Adjacency * adjacency;

    for (v = 0; v < vertices; v++)
    {
        st[v] = -1;
        wt[v] = MAX_DISTANCE;

        newint =	(int*) malloc(sizeof(int));
        VerifyMalloc((Item) newint);
        *newint = v;
        HeapInit(heap, (Item) newint); //Se nao funcionar pode ser esta wannabe passagem por referencia
    }
    wt[s] = 0;
    st[s] = s;
    FixUp(heap, s, wt);

    while (HeapEmpty(heap))
    {
        v = *((int *)RemoveMin(heap, wt)); /*Removes the min value form the heap, returns it, and makes the array an heap again*/
        //printf("Remove min \n");
        //PrintMe(heap);
        aux = v;
        if (wt[v] != MAX_DISTANCE)
        {
            for (t = GetGraphAdjHead(G, v); t != NULL; t=getNextNodeLinkedList(t))
            {
                adjacency = (Adjacency*) getItemLinkedList(t);
                w = GetAdjacencyVertice (adjacency);
                weight = GetAdjacencyWeight(adjacency);

                if( wt[w] > (wt[v] + ( weight * weight_mult_factor))  && GetFlagRes(w, decoder) != 1)  /*If he's walking weight_mult_factor = 3; if he's on the car weight_mult_factor = 1;*/
                   {
                       wt[w] = wt[v] + ( weight * weight_mult_factor);
                       st[w] = v;
                       FixUp(heap, w, wt);
                       //printf("Fix up \n");
                       //PrintMe(heap);
                   }
            }
        }
        n_elements = GetHeapN_Elements(heap);
    }
}

void PathCalculator(Graph *G, int entry, ListNode** carpath, ListNode** footpath, Array decoder, ListNode * accesseshead, char objective, int vertices)
{
  int *stcar, *wtcar, *stfoot, *wtfoot, *staux, *wtaux;
  int accesspos, bestpathweight = MAX_DISTANCE, pathweight, index, bestparkingspot;
  char accesstype;
  ListNode * freespotshead, *auxaccess, *freespotsaux;

  /*Allocs memmory for the st/wt with the lowest path and for the st/wt we're currently analysing */
  /*Used for the part of the path made in the car */
  wtcar = (int*)malloc(sizeof(int) * vertices);
  VerifyMalloc((Item) wtcar);
  stcar = (int*)malloc(sizeof(int) * vertices);
  VerifyMalloc((Item) stcar);
  /*Used to save the best path and corresponding weight */
  wtfoot = (int*)malloc(sizeof(int) * vertices);
  VerifyMalloc((Item) wtfoot);
  stfoot = (int*)malloc(sizeof(int) * vertices);
  VerifyMalloc((Item) stfoot);
  /*Used for each access of the pretended type */
  wtaux = (int*)malloc(sizeof(int) * vertices);
  VerifyMalloc((Item) wtaux);
  staux = (int*)malloc(sizeof(int) * vertices);
  VerifyMalloc((Item) staux);


  Dijsktra(G, entry, stcar, wtcar, 1, decoder); //Dijsktra for path inside the car

  freespotshead = FindFreeSpots(decoder, vertices);

  auxaccess = accesseshead;

  while(auxaccess != NULL) /*Goes through the list of accesses and calculates the path from the wanted access to every parking spot */
  {
    accesspos =  *((int *)(getItemLinkedList(auxaccess)));
    accesstype = GetIP_Type(accesspos, decoder);
    if(accesstype == objective )
    {
     	 Dijsktra(G, accesspos , staux, wtaux, 3, decoder); //Dijsktra for path inside the car


        freespotsaux = freespotshead;
        //PrintIntList(freespotsaux);
      	while(freespotsaux != NULL)
        {
          index = *((int *)(getItemLinkedList(freespotsaux)));

          pathweight = wtcar[index] + wtaux[index];

          if( pathweight < bestpathweight)
          {
           bestpathweight = pathweight;
           bestparkingspot = index;
           wtfoot = wtaux;
           stfoot = staux;
          }
          freespotsaux = getNextNodeLinkedList(freespotsaux);
        }


    }
  	auxaccess = getNextNodeLinkedList(auxaccess);
  }


  //=====>  MUDAR DJIKSTRA PARA VER RESTRIÇOES
  // NÃO ESQUECER DE FAZER FREE NOS FREESPOTS

  CreatePathListBackwards(footpath, stfoot, bestparkingspot);
  CreatePathList(carpath, stcar, bestparkingspot);


}

void CreatePathListBackwards(ListNode** footpath, int* stfoot, int bestparkingspot)
{
  int position;
  int * i;

  position = stfoot[bestparkingspot];

  if(position != stfoot[position])
    CreatePathListBackwards(footpath, stfoot, position);

  i = (int*) malloc( sizeof(int) );
  VerifyMalloc(i);

  *i = position;

  *footpath = AddNodeToListHead(*footpath, (Item) i);

}


void CreatePathList(ListNode** carpath, int* stcar, int bestparkingspot)
{
  int pos;
  int * i;


   for(pos = bestparkingspot; pos != stcar[pos]; pos = stcar[pos])
   {
       i = (int*)malloc(sizeof(int));
      *i = pos;
      *carpath = AddNodeToListHead(*carpath, (Item) i);
   }

   //Last case
    i = (int*)malloc(sizeof(int));
    *i = pos;
    *carpath = AddNodeToListHead(*carpath, (Item) i);


}
