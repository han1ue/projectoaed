#include "Defs.h"

typedef struct arraynode ArrayNode;
typedef ArrayNode ** Array;

Array InitArray(int);
Item GetArrayNodeItem(int, Array);
Item ModifyArrayNodeItem(int, Item, Array);
void DeleteNodeItem(int, Array);
