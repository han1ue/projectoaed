#include "LinkedList.h"
#include "ParkingLot.h"
#include "Defs.h"


typedef struct reststruct Rest;
ListNode * RestListInit( FILE* carconfig, FILE* resconfig );
int GetRestTime(Rest* Rest);
int CompareRestTime(Item Rest1, Item Rest2, int direction);
char GetRestFlag(Rest* Rest);
int GetRestCoord(Rest* Rest, char coord);
void PrintRestList(ListNode*);
