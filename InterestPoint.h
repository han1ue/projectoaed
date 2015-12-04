#include "Defs.h"

typedef struct interestpoint InterestPoint;
Array GraphDecoderInit(char ***, int, int, int, int, int*);
char GetIP_Type(int, Array);
int GetIP_Coord(int, char, Array);
int FindIP(int, int, int, int, Array);
void OccupyPos(int, Array, int);
void FreePos(int, Array, int);
int GetFlagRes(int, Array);
//ListNode * HandleRestriction(Graph *, ListNode *, Event *, Array, ListNode *, int, ParkingLot *);
void ReleasePos(int, Array decoder);
void RestrictPos(int, Array decoder);
void ChangeIP_Type(int i, Array decoder, char type);
ListNode * FindFreeSpots(Array, int);
