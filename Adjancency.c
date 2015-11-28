#include "Defs.h"

struct adjacency
{
    int vertice;
    int weight;
};

/******************************************************************************
 * InsertAdjacency
 *
 * Arguments: x,y,z - position of the graph insertion
 *        		type - type of the position
 *            listhead - the head of the adjanceny list for this vertice
 *						decoder - map decoder
 * Returns: pointer to the head of the adjancency list for this vertice
 *
 *****************************************************************************/

ListNode * InsertAdjacency(int vertices, int x, int y, int z, char type, ListNode* listhead, Array decoder)
{
    Adjacency* adjacencynode = (Adjacency *) malloc(sizeof(Adjacency) );

    adjacencynode->vertice = FindIP(vertices, x, y, z, decoder);

    if(type == 'u' || type == 'd')
       adjacencynode->weight = 2;
       else
       adjacencynode->weight = 1;

       listhead = AddNodeToListHead(listhead, (Item) adjacencynode);

       return listhead;
       }

    /******************************************************************************
     * InitAdj
     *
     * Arguments: vertices - number of vert in the graph
     *        		matrix - 3d string of the parkinglot
     *            decoder - aux array that contains info about the vertices
     * Returns: pointer to parking floor
     *
     *****************************************************************************/

       Array InitAdj(int vertices, char *** matrix, Array decoder, int col, int row, int floors)
    {
        Array adj;
        int i, x, y, z, *vertice;
        char type;
        ListNode * listhead;

        adj = InitArray(vertices);

        for(i=0; i<vertices; i++)
        {
            listhead = NULL;

            x = GetIP_Coord(i, 'x', decoder);       /*Gets the first int of the InterestPoint i in the array */
            y = GetIP_Coord(i, 'y', decoder);			  /*Gets the second int of the InterestPoint i in the array */
            z = GetIP_Coord(i, 'z', decoder);		    /*Gets the third int of the InterestPoint i in the array */
            type = GetIP_Type(i, decoder);				  /*Gets the type of the InterestPoint i in the array */


            /*Special case for inserting adj vertices for parking spots because we dont want them to be adjacent with other parking spots*/
            if ( type == '.')
            {
                if( (x+1 < col) && (matrix[x+1][y][z] != '@') && (matrix[x+1][y][z] != '.'))
                    listhead = InsertAdjacency(vertices, x+1, y, z, type, listhead, decoder);

                if( (x-1 >= 0) && (matrix[x-1][y][z] != '@') && (matrix[x-1][y][z] != '.'))
                    listhead = InsertAdjacency(vertices, x-1, y, z, type, listhead, decoder);

                if( (y+1 < row) && (matrix[x][y+1][z] != '@') && (matrix[x][y+1][z] != '.'))
                    listhead = InsertAdjacency(vertices, x, y+1, z, type, listhead, decoder);

                if( (y-1 >= 0) && (matrix[x][y-1][z] != '@') && (matrix[x][y-1][z] != '.'))
                    listhead = InsertAdjacency(vertices, x, y-1, z, type, listhead, decoder);

            }
            /*If's to find the adjacent vertices for the ramps */
            else if( type == 'd' )
                listhead = InsertAdjacency(vertices, x, y, z-1, type, listhead, decoder);

            else if( type == 'u' )
                listhead = InsertAdjacency(vertices, x, y, z+1, type, listhead, decoder);

            else
            {
                /*The 4 following if's will find the adjacents of the vertice "i" that are in the same floor*/
                if( (x+1 < col) && (matrix[x+1][y][z] != '@'))
                    listhead = InsertAdjacency(vertices, x+1, y, z, type, listhead, decoder);

                if( (x-1 >= 0) && (matrix[x-1][y][z] != '@'))
                    listhead = InsertAdjacency(vertices, x-1, y, z, type, listhead, decoder);

                if( (y+1 < row) && (matrix[x][y+1][z] != '@'))
                    listhead = InsertAdjacency(vertices, x, y+1, z, type, listhead, decoder);

                if( (y-1 >= 0) && (matrix[x][y-1][z] != '@'))
                    listhead = InsertAdjacency(vertices, x, y-1, z, type, listhead, decoder);

            }

            ModifyArrayNodeItem(i, (Item) listhead, adj);
        }
        return adj;
    }

int GetAdjacencyVertice(Adjacency * adjacency)
{
    int a =adjacency->vertice;
    return adjacency->vertice;
}

int GetAdjacencyWeight(Adjacency * adjacency)
{
    return adjacency->weight;
}
