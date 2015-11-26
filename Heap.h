#include "Defs.h"


typedef struct _heap Heap;

Heap *NewHeap(int size, int (*comparison) (Item, Item));

void FreeHeap(Heap * h);

void FixUp(Heap *, int, int*);

void FixDown(Heap *, int, int*);

int HeapInit(Heap *, Item);

int HeapEmpty(Heap*);

Item RemoveMin(Heap * h, int *);

