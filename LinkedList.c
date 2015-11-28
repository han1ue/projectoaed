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

void ModifyPointerNext(ListNode* node, ListNode* pointer)
{
    /* Check if node is not empty                                   */
    if(node == NULL || pointer == NULL)
    {
        printf("Error. One of the nodes you're trying to use is NULL.");
        exit(-1);
    }

    node->next = pointer;
}


void InsertNodeAfter(ListNode* toinsert, ListNode* ref)
{
    /* Check if node is not empty                                   */
    if(ref == NULL || toinsert == NULL)
    {
        printf("Error. One of the nodes you're trying to use is NULL.");
        exit(-1);
    }

    toinsert->next = ref->next;
    ref->next = toinsert;
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

/******************************************************************************
 * insertSortedLinkedList
 *
 * Arguments: head - pointer to the current head
 *            this - item to insert in the list
 *
 * Returns: head of the list
 *
 *****************************************************************************/
ListNode * insertSortedLinkedList(ListNode * head, Item this, int (* CompareFunction)(Item item1, Item item2, int direction), int direction)
{
    ListNode * new, * aux;
    int a, b;
    int thead, taux, tatual;

    /* Memory allocation                                            */
    new = (ListNode *) malloc(sizeof(ListNode));
    VerifyMalloc( (Item) new );

    new->this = this;

    /*If the list has 0 elements or the item to insert is lower than the first in the current list */
    if(head == NULL || (CompareFunction( (head->this), this, direction)) )
    {
        new->next = head;
        head = new;
        return head;
    }



    aux = head;


    while( aux->next != NULL && ( !(CompareFunction((aux->next->this), this, direction)) ) )
    {
        aux = aux->next;
    }

    new->next = aux->next;
    aux->next = new;

    return head;
}

void PrintIntList(ListNode* head)
{
    ListNode* aux = head;
    int toprint, toprint2;
    Adjacency* adjacencynode;

    if(aux == NULL)
    {
        printf("Error. You can't print an empty list.");
        exit(-1);
    }
    while(aux!=NULL)
    {
        adjacencynode = (Adjacency*) (aux->this);
        toprint = GetAdjacencyVertice(adjacencynode);
        toprint2 = GetAdjacencyWeight(adjacencynode);
        printf("%d;%d ", toprint, toprint2);
        aux = aux->next;
    }
}
