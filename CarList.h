#include "Defs.h"

typedef struct carstruct Car;


Car* CarListInit(Event *, ParkingLot *);
char GetCarStatus(Car*);
int CompareCarStatus(Item , Item, int);
ListNode* RemoveCar(ListNode*, Array, int, char *);
void PrintCarList(ListNode*);
ListNode* AddCar(ListNode * carlisthead, char * carname, int x, int y, int z, char objective, Array decoder, int vertices, Graph * graph, ListNode* accesseshead);
