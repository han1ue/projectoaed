#include "Defs.h"

struct graph
{
    int v;
    int e;
    Array adj;
};

/******************************************************************************
 * GraphInit
 *
 * Arguments: vertices - number of vert in the graph
 *						matrix - 3d map of the parkinglot
 *        		decoder - aux array that contains info about the vertices
 * Returns: pointer to the created graph
 *
 *****************************************************************************/

Graph *GraphInit(int vertices, char *** matrix, Array decoder, int col, int row, int floors)
{
    Graph *G = (Graph*) malloc( sizeof(Graph) ); /*antes estava sizeof(struct graph)*/
    VerifyMalloc( (Item) G );
    G->v = vertices;
    G->e = 0;
    G->adj = InitAdj(vertices, matrix, decoder, col, row, floors);
    return G;
}


void PrintGraph(Graph* g, int vertices)
{
    int i;
    ListNode* head;
    char test;

    printf("Do you want to print all the vertices? [y/n]");
    scanf("%c", &test);

    if (test == 'y'){
        for (i=0; i<vertices; i++)
        {
            printf("V:%d --> ", i);  /*Prints the head of the adj list we are printing */
            head = (ListNode*) GetArrayNodeItem(i, g->adj);
            PrintIntList(head);
            printf("\n");

        }
    }
    else if (test == 'n')
    {
        printf("Which one do you want to print?");
        scanf("%d", &i);
        printf("V:%d --> ", i);  /*Prints the head of the adj list we are printing */
        head = (ListNode*) GetArrayNodeItem(i, g->adj);
        PrintIntList(head);
        printf("\n");
    }
    else printf("Not a valid answer.");
}

int GetGraphVertices(Graph *g)
{
    return g->v;
}

ListNode* GetGraphAdjHead(Graph *g, int i)
{
    return (ListNode*)g->adj[i];
}
