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



void Dijsktra(Graph *G, int s, int* st, int* wt, int weight_mult_factor)
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
        printf("Remove min \n");
        PrintMe(heap);
        //FreeLastHeapPos(heap);
        if (v == 32) {
            printf("ola");
        }
        aux = v;
        if (wt[v] != MAX_DISTANCE)
        {
            for (t = GetGraphAdjHead(G, v); t != NULL; t=getNextNodeLinkedList(t))
            {
                adjacency = (Adjacency*) getItemLinkedList(t);
                w = GetAdjacencyVertice (adjacency);
                weight = GetAdjacencyWeight(adjacency);

                if( wt[w] > (wt[v] + ( weight * weight_mult_factor))  && w nao esta restrito)  /*If he's walking weight_mult_factor = 3; if he's on the car weight_mult_factor = 1;*/
                   {
                       wt[w] = wt[v] + ( weight * weight_mult_factor);
                       st[w] = v;
                       FixUp(heap, w, wt);
                       printf("Fix up \n");
                       PrintMe(heap);
                   }
            }
        }
        n_elements = GetHeapN_Elements(heap);
    }
}

void PathCalculator(Graph *G, int entry, ListNode** carpath, ListNode** footpath, Array decoder, ListNode * accesseshead, char objective, int vertices)
{
  int * wtcar, * wtfoot, *staux, *wtaux;
  int accesstype, accesspos, bestpathweight = MAX_DISTANCE, pathweight, index, bestparkingspot;
  ListNode * freespots, *auxaccess, *auxfreespots;
  
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
  
  
  Dijsktra(graph, i, stcar, wtcar, 1); //Dijsktra for path inside the car
  
  freespotshead = FindFreeSpots(decoder, vertices);
  
  auxaccess = accesseshead;
  
  while(auxaccess != NULL) /*Goes through the list of accesses and calculates the path from the wanted access to every parking spot */
  {
    accesspos =  *((int *)(getItemLinkedList(auxaccess)));
    accesstype = GetIP_Type(accesspos, decoder));
    if(accesstype) == objective )
    {
     	 Dijsktra(graph, accesspos , staux, wtaux, 3); //Dijsktra for path inside the car
      
      	
        auxfreespots = freespotshead;
      	while(freespotsaux != NULL)
        {
          index = *((int *)(getItemLinkedList(freespotaux), decoder));
          
          pathweight = wtcar[index] + wtaux[index];
          
          if( pathweight < bestpathweight)
          {
           bestpathweight = pathweight;
           bestparkingspot = index;
           wfoot = wtaux;
           stfoot = staux;
          }
        }
          
      
    } 
  	auxaccess = getNextNodeLinkedList(auxaccess);
  }
  
  
  =====>  MUDAR DJIKSTRA PARA VER RESTRIÇOES
  // NÃO ESQUECER DE FAZER FREE NOS FREESPOTS
  
  *footpath = CreatePathListBackwards(*footpath, stfoot, bestparkingspot);
  *carpath = CreatePathList(*carpath, stfoot, bestparkingspot);
 
  
}

ListNode * CreatePathListBackwards(ListNode* footpath, int* stfoot, int bestparkingspot)
{
  int position;
  int * i;
  
  position = stfoot[bestparkingspot];
  
  if(position != stfoot[position])
    footpath = CreatePathListBackwards(footpath, stfoot, position)
  
  i = (int*) malloc( sizeof(int) );
  VerifyMalloc(i);
  
  *i = position;
  
 	footpath = AddNodeToListHead(footpath, (Item) i);
  
  return footpath;
}


ListNode * CreatePathList(ListNode*carpath, int* stfoot, int bestparkingspot)
{
  int pos;
  int * i;
  
  
   for(pos = bestparkingspot; pos != auxcar->path[pos]; pos = stfoot[bestparkingspot])
   {
    	i = (int*)malloc(sizeof(int));
      *i = position;
      carpath = AddNodeToListHead(carpath, (Item) i);
   }
  
  return carpath;
}
