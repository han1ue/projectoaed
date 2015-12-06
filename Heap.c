/******************************************************************************
 *
 * File Name: heap.c
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 *
 * NAME
 *     Heap11 - Heap operations
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <malloc.h>
 *
 * DESCRIPTION
 *		implements tree auxiliary functions
 * DIAGNOSTICS tested
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"

/* to remove comments, just delete or comment the next line */
#define DEMO

/* A heap is represented by a structure: */
struct _heap {
  int (*comparison) (Item, Item);     /* Surprise! this field is a function pointer* to elements in the heap. */
  int n_elements; 	            /* # elements in heap */
  int size;                     /* max size of the heap. */
  Item *heapdata;               /* An array of Items. */
};

void (*PrintItem) (Item);


void PrintMe(Heap* h)
{
    int v = h->n_elements;
    int c;
    for (c=0; c<v; c++ )
    {
        printf("%d ", *((int*)(h->heapdata[c])) );
    }
    printf("\n");
}

/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 *
 *****************************************************************************/

Heap *NewHeap(int size, int (*comparison) (Item, Item))
{
  Heap *h;

  h = (Heap *) malloc(sizeof(Heap));
  VerifyMalloc((Item) h);
  if (h == ((Heap *) NULL)) {
    fprintf(stderr, "Error in malloc of heap\n");
    exit(1);
  }

  h->n_elements = 0;
  h->comparison = comparison;
  h->size = size;
  h->heapdata = (Item *) malloc(size * sizeof(Item));
  VerifyMalloc((Item) h->heapdata);
  if (h->heapdata == ((Item *) NULL)) {
    fprintf(stderr, "Error in malloc of heap data\n");
    exit(1);
  }

  return (h);
}

/******************************************************************************
 * HeapInit()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap but does not perform fixup
 *
 *****************************************************************************/

int HeapInit(Heap * h, Item element)
{
  if (h->n_elements == h->size) {
    printf("Heap full (size = %d) !\n", h->size);
    return 0;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;

  return 1;
}

/******************************************************************************
 * FixUp()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixup
 * Returns:
 * Side-Effects: none
 *
 * Description: Performs fixup from index
 *
 *****************************************************************************/

void FixUp(Heap * h, int a, int* wt)
{
  Item t;
  int k;

  for(k=0; a != *((int*)h->heapdata[k]); k++);

  while ((k > 0) && (h->comparison) ((Item) &wt[*((int*)h->heapdata[(k - 1) / 2])], (Item) &wt[*((int*)h->heapdata[k])]))
  {


    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
    (h->heapdata)[(k - 1) / 2] = t;


    k = (k - 1) / 2;
  }

  return;
}

/******************************************************************************
 * FixDown()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixdown
 * Returns:
 * Side-Effects: none
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/

void FixDown(Heap * h, int k, int* wt)
{
  int j;
  Item t;

  while ((2 * k + 1) < h->n_elements)
  {
    j = 2 * k + 1;
    if (((j + 1) < h->n_elements) && (h->comparison) ((Item) &wt[*((int*)h->heapdata[j])], (Item) &wt[*((int*)h->heapdata[j+1])])) {
      /* second offspring is smaller than its brother */
      j++;
    }

    if (!(h->comparison) ((Item) &wt[*((int*)h->heapdata[k])], (Item) &wt[*((int*)h->heapdata[j])])) {
      /* Elements are already in correct order. */
      break;
    }

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;
    k = j;
  }

  if ((h->comparison) ((Item) &wt[*((int*)h->heapdata[k])], (Item) &wt[*((int*)h->heapdata[k+1])]))
  {
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[k+1];
    (h->heapdata)[k+1] = t;
  }

  return;
}

/******************************************************************************
 * RemoveMin
 *
 * Arguments: h - pointer to heap
 *
 * Returns: Item inse the min value of the heap
 *
 *
 *****************************************************************************/

Item RemoveMin(Heap * h, int * wt)
{
  Item t;

  if (h->n_elements > 0)
  {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    h->n_elements--;
    FixDown(h, 0, wt);
    return t;
  }

  return NULL;
}

void FreeLastHeapPos(Heap* h)
{
    free(h->heapdata[h->n_elements - 1]);
    h->n_elements--;
    return;
}


int HeapEmpty(Heap* h)
{
    if (h->n_elements == 0)
        return 0;
    else return 1;
}


int GetHeapN_Elements(Heap* h)
{
    return (h->n_elements);
}

int GetFirstElement(Heap* h)
{
    return ( *((int*) h->heapdata[0]) );
}

int IsAllInfinity(Heap* h)
{
    int i;
    for(i=0;i<h->n_elements;i++)
    {
        if( *( (int*) h->heapdata[i]) != 10000)
        {
            return 0;
        }
    }
    return 1;
}




/******************************************************************************
 * FreeHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/

void FreeHeap(Heap *h, int vertices)
{
    int c;

    for (c=0; c < vertices; c++)
    {
        free(h->heapdata[c]);
    }
    free(h->heapdata);
    free (h);

    return;
}
