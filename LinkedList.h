#include "Defs.h"

typedef struct listnode ListNode;

ListNode* AddNodeToListHead(ListNode *, Item);
void freeLinkedList(ListNode * first);
int lengthLinkedList(ListNode * first);
ListNode * getNextNodeLinkedList(ListNode * node);
Item getItemLinkedList(ListNode * node);
