#include "Defs.h"

struct listnode
{
	Item this;
  struct listnode * next;
};




ListNode* AddNodeToListHead(ListNode *head, Item this)
{
  ListNode * new = (ListNode *)malloc(sizeof(ListNode));
  VerifyMalloc( (Item) new );
  new->this = this;
  new->next=head;
  head = new;

  return head;
}


Item getItemLinkedList(ListNode * node)
{
  /* Check if node is not empty                                   */
  if(node == NULL)
    return NULL;

  return node->this;
}

void freeLinkedList(ListNode * head)
{
  ListNode * next;
  ListNode * aux;

  /* Cycle from the first to the last element                     */
  for(aux = head; aux != NULL; aux = next)
  {
    /* Keep trace of the next node                                */
    next = aux->next;

    /* Free current item                                          */
		free(aux->this);

    /* Free current node                                          */
    free(aux);
  }

  return;
}

/*
 *  Function:
 *    lengthLinkedList
 *
 *  Description:
 *    Determines the length of a linked list.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *        (LinkedList *) first
 *
 *  Return value:
 *    Returns the length of the linked list.
 */
int lengthLinkedList(ListNode * head)
{
  ListNode * aux;
  int counter;

  /* Length determination cycle                                   */
  for(aux = head, counter = 0;aux!=NULL;counter++, aux = aux->next);

  return counter;
}

/*
 *  Function:
 *    getNextNodeLinkedList
 *
 *  Description:
 *    Returns the next node of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the next node of a linked list. NULL
 *   is returned in case the current node is empty or there is no
 *   node following the current node.
 */
ListNode * getNextNodeLinkedList(ListNode * node)
{
  return ((node == NULL) ? NULL : node->next);
}
