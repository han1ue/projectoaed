#include "LinkedList.h"
#include "ParkingLot.h"
#include "Defs.h"


typedef struct reststruct Rest;
ListNode* RestInit(FILE*);
ListNode * HandleRest(ListNode*, ParkingLot*, int, FILE*);
int GetRestTime(Rest*);
int CompareRestTime(Item, Item, int);
char GetRestFlag(Rest*);
int GetRestCoord(Rest*, char);
int IsFloorRestricted( int, ParkingLot *);
void RestrictWholeFloor( int, ParkingLot *);
void ReleaseWholeFloor( int, ParkingLot *);
/*void PrintRestList(ListNode*);*/
