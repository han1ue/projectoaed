#include "Defs.h"
int Comparison(Item, Item);
void Dijsktra(Graph *, int, int*, int*, int, Array);
int PathCalculator(Graph *, int, ListNode**, ListNode**, Array, ListNode *, char, int);
void CreatePathListBackwards(ListNode**, int*, int);
void CreatePathList(ListNode**, int*, int);
int CheckRamp(int, int, int *, Array);
int CheckConnection(char, int);
