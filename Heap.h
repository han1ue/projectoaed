#include "Defs.h"


typedef struct _heap Heap;

Heap *NewHeap(int size, int (*comparison) (Item, Item));

void FreeHeap(Heap * h);

void FixUp(Heap * h, int k, int* wt);

int Insert(Heap * h, Item element);

int Direct_Insert(Heap * h, Item element);

void Modify(Heap * h, int indice, Item newvalue);

Item RemoveMax(Heap * h);

void CleanHeap(Heap * h);

int VerifyHeap(Heap * h);

void HeapSort(Heap * h);

void Heapify(Heap * h);


Funções a por no main/client 
================================================================
================================================================
void ModifyNum(Heap * h)
{
  int indice;
  int *novovalor = (int *) malloc(sizeof(int));

  printf("Index of the element to change: ");
  scanf("%d", &indice);
  printf("New value: ");
  scanf("%d", novovalor);
  Modify(h, indice, (Item) novovalor);

  return;
}
================================================================

