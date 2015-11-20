#include "Defs.h"


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

        /*The 4 following if's will find the adjacents of the vertice "i" that are in the same floor*/
        if( (x+1 < col) && (matrix[x+1][y][z] != '@'))
        {
            listhead = AddNodeToListHead(listhead, (Item) FindIP(vertices, x+1, y, z, decoder) );
        }
        if( (x-1 >= 0) && (matrix[x-1][y][z] != '@'))
        {
            listhead = AddNodeToListHead(listhead, (Item) FindIP(vertices, x-1, y, z, decoder) );
        }
        if( (y+1 < row) && (matrix[x][y+1][z] != '@'))
        {
            listhead = AddNodeToListHead(listhead, (Item) FindIP(vertices, x, y+1, z, decoder) );
        }
        if( (y-1 >= 0) && (matrix[x][y-1][z] != '@'))
        {
            listhead = AddNodeToListHead(listhead, (Item) FindIP(vertices, x, y-1, z, decoder) );
        }

        /*If's to find the adjacent vertices for the ramps */
        if( (type == 'd') )
        {
            listhead = AddNodeToListHead(listhead, (Item) FindIP(vertices, x, y, z-1, decoder) );
        }
        if( (type == 'u') )
        {
            listhead = AddNodeToListHead(listhead, (Item) FindIP(vertices, x, y, z+1, decoder) );
        }

        ModifyArrayNodeItem(i, (Item) listhead, adj);
    }
    return adj;
}
