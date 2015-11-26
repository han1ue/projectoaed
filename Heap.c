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
  if (h == ((Heap *) NULL)) {
    fprintf(stderr, "Error in malloc of heap\n");
    exit(1);
  }

  h->n_elements = 0;
  h->comparison = comparison;
  h->size = size;
  h->heapdata = (Item *) malloc(size * sizeof(Item));
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

void FixUp(Heap * h, int k, int* wt)
{
  Item t;
  while ((k > 0) && (h->comparison) ((Item) &wt[(k - 1) / 2], (Item) &wt[k])) //Se der bug pode ser dos pointers a entrar aqui
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
    if (((j + 1) < h->n_elements) &&
        (h->comparison) ((Item) wt[j], (Item) wt[j])) {
      /* second offspring is greater */
      j++;
    }
    if (!(h->comparison) ((Item) wt[k], (Item) wt[j])) {
      /* Elements are in correct order. */
      break;
    }

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;
    k = j;
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
    free(h->heapdata[h->n_elements - 1]);
    h->n_elements--;
    FixDown(h, 0, wt);
    return t;
  }

  return NULL;
}

int HeapEmpty(Heap* h)
{
    if (h->n_elements == 0)
        return 0;
    else return 1;
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

void FreeHeap(Heap *h)
{
    int c;

    for (c=0; c < h->n_elements; c++)
    {
        free(h->heapdata[c]);
    }
    free(h->heapdata);
    free (h);

    return;

}
