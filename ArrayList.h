#include "Defs.h"

typedef struct arraynode ArrayNode;
typedef ArrayNode ** Array;

Array InitArray(int);
Item * GetArrayNodeItem(int, Array);
void ModifyArrayNodeItem(int, Item, Array);
void DeleteNodeItem(int, Array);
