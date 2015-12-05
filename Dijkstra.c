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

    return (aa >= bb);
}



void Dijsktra(Graph *G, int s, int* st, int* wt, int weight_mult_factor, Array decoder)
{
    int v, w, vertices, *newint, weight, n_elements;
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

      // printf("antes do removemin \n");
      // PrintMe(heap);

       v = *((int *)RemoveMin(heap, wt)); /*Removes the min value form the heap, returns it, and makes the array an heap again*/

       //printf("depois do removemin \n");
      // PrintMe(heap);

        if (wt[v] != MAX_DISTANCE && GetIP_Type(v, decoder) != '.') /* != '.' because it cant circulate over parking spots */
        {
            if(CheckConnection(GetIP_Type(v, decoder), weight_mult_factor) == 1)
            {

                for (t = GetGraphAdjHead(G, v); t != NULL; t=getNextNodeLinkedList(t))
                {
                    adjacency = (Adjacency*) getItemLinkedList(t);
                    w = GetAdjacencyVertice (adjacency);
                    weight = GetAdjacencyWeight(adjacency);

                    if( wt[w] > (wt[v] + ( weight * weight_mult_factor)) && GetFlagRes(w, decoder) != 1 && CheckRamp(v, w, st, decoder) && GetIP_Type(w, decoder) != 'x')  /*If he's walking weight_mult_factor = 3; if he's on the car weight_mult_factor = 1;*/
                    {
                           wt[w] = wt[v] + ( weight * weight_mult_factor);
                           st[w] = v;
                           FixUp(heap, w, wt);
                          // printf("Fix up \n");
                          // PrintMe(heap);
                    }
                }
            }
        }
    }
}

int PathCalculator(Graph *G, int entry, ListNode** carpath, ListNode** footpath, Array decoder, ListNode * accesseshead, char objective, int vertices)
{
  int *stcar, *wtcar, *stfoot, *wtfoot, *staux, *wtaux;
  int accesspos, bestpathweight = MAX_DISTANCE, pathweight, index, bestparkingspot, bestfoot;
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
  //PrintIntList(freespotshead);
  auxaccess = accesseshead;
  //printf("Lista de acessos: \n");
  //PrintIntList(accesseshead);

  while(auxaccess != NULL) /*Goes through the list of accesses and calculates the path from the wanted access to every parking spot */
  {
    accesspos =  *((int *)(getItemLinkedList(auxaccess)));
    //PrintIntList(auxaccess);
    accesstype = GetIP_Type(accesspos, decoder);
    if(accesstype == objective )
    {
     	 Dijsktra(G, accesspos , staux, wtaux, 3, decoder); //Dijsktra for path inside the car

        freespotsaux = freespotshead;
      	while(freespotsaux != NULL)
        {
          index = *((int *)(getItemLinkedList(freespotsaux)));

          pathweight = wtcar[index] + wtaux[index];

          if( pathweight < bestpathweight)
          {
           bestpathweight = pathweight;
           bestfoot = wtaux[index];
           bestparkingspot = index;
           CpyIntVector(wtfoot, wtaux, vertices);
           CpyIntVector(stfoot, staux, vertices);
          }
          else if(pathweight == bestpathweight) /*Project Decision: if two paths weight exatcly the same we choose the one with least effort ~ less foot path */
          {
              if(bestfoot > wtaux[index])
              {
                  bestpathweight = pathweight;
                  bestfoot = wtaux[index];
                  bestparkingspot = index;
                  CpyIntVector(wtfoot, wtaux, vertices);
                  CpyIntVector(stfoot, staux, vertices);
              }
          }
          freespotsaux = getNextNodeLinkedList(freespotsaux);
        }


    }
  	auxaccess = getNextNodeLinkedList(auxaccess);
  }

  // NÃO ESQUECER DE FAZER FREE NOS FREESPOTS
  CreatePathList(carpath, stcar, bestparkingspot);
  CreatePathListBackwards(footpath, stfoot, bestparkingspot);
  /*

  PrintIntList(*carpath);

  PrintIntList(*footpath);*/

  return bestpathweight;
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

int CheckRamp(int v, int w, int * st, Array decoder)
{
    char type_v, type_w, type_st_v;

    type_v = GetIP_Type(v, decoder);

    if(type_v != 'u' && type_v != 'd')
        return 1;
    else
    {
        type_st_v = GetIP_Type(st[v], decoder);

        if(type_st_v == 'u'|| type_st_v == 'd')
        {
            if( GetIP_Coord(w, 'z', decoder) == GetIP_Coord(v, 'z', decoder) )
                return 1;
            else
                return 0;
        }
        else
        {
            if( GetIP_Coord(w, 'z', decoder) == GetIP_Coord(v, 'z', decoder) )
                return 0;
            else
                return 1;
        }

    }
}


int CheckConnection(char type, int weight) /*In free spots and accesses we want other positions to be able to get there but  */
{
    if (weight == 3)
        return 1;
    else
    {
        if (type == 'E' || type == 'C' || type == 'L' || type == 'H' || type == 'R')
            return 0;
        else
            return 1;
    }
}


void CpyIntVector(int* stfoot, int* staux, int vertices)
{
    int i;

    for (i=0; i<vertices; i++)
    {
        stfoot[i] = staux[i];
    }
}
