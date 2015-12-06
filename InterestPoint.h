#include "Defs.h"

typedef struct interestpoint InterestPoint;
Array GraphDecoderInit(char ***, int, int, int, int, int*);
char GetIP_Type(int, Array);
int GetIP_Coord(int, char, Array);
int FindIP(int, int, int, int, Array);
void OccupyPos(int, Array);
void FreePos(int, Array);
int GetIP_Flagres(int, Array);
void ReleasePos(int, Array decoder);
void RestrictPos(int, Array decoder);
void ChangeIP_Type(int i, Array decoder, char type);
ListNode * FindFreeSpots(Array, int);
void FreeDecoder(Array , int );
