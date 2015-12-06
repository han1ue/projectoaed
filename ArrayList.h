#include "Defs.h"

typedef Item * Array;

Array InitArray(int);
Item GetArrayNode(int, Array);
void ModifyArrayNode(int, Item, Array);
void DeleteNodeItem(int, Array);
