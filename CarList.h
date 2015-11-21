#include "Defs.h"

typedef struct carstruct Car;


Car* CarListInit(Event *, Array, int);
char GetCarStatus(Car*);
int CompareCarStatus(Item , Item, int);
ListNode* RemoveCar(NodeList*, Array, int);
