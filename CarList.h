#include "Defs.h"

typedef struct carstruct Car;


Car* CarListInit(Event *, ParkingLot *);
char GetCarStatus(Car*);
int CompareCarStatus(Item , Item, int);
ListNode * RemoveCar(Graph * graph, ListNode * carlisthead, ListNode * accesseshead, Array decoder, int vertices, char * carname);
void PrintCarList(ListNode*);
ListNode* AddCar(ListNode * carlisthead, char * carname, int x, int y, int z, char objective, Array decoder, int vertices, Graph * graph, ListNode* accesseshead, int freespots);
ListNode * HandleQueue(Graph * graph, Array decoder, ListNode * accesseshead, ListNode * carlisthead, int vertices);
