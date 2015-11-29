#include "Defs.h"

typedef struct listnode ListNode;

ListNode* ListInit(ListNode*);
ListNode* AddNodeToListHead(ListNode *, Item);
void freeLinkedList(ListNode * first);
int lengthLinkedList(ListNode * first);
ListNode * getNextNodeLinkedList(ListNode * node);
Item getItemLinkedList(ListNode * node);
void InsertNodeAfter(ListNode*, ListNode*);
void ModifyPointerNext(ListNode*, ListNode*);
ListNode * insertSortedLinkedList(ListNode * head, Item this, int (* CompareFunction)(Item item1, Item item2, int direction), int direction);
void PrintIntList(ListNode*);
