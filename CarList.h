#include "Defs.h"

typedef struct carstruct Car;


Car* CarListInit(Event * eventlisthead);
char GetCarStatus(Car* car);
int CompareCarStatus(Item car1, Item car2, int direction);
void PrintCarList(ListNode*);
