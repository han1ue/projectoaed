#include "Defs.h"

/******************************************************************************
 * VerifyMalloc
 *
 * Arguments: pointer - pointer to variable we malloc'ed earlier to check if it went through
 *
 * Returns: none; prints error and exits the program if the malloc didn't go as planned
 *
 *****************************************************************************/

void VerifyMalloc(Item pointer)
{
    if(pointer == NULL)
    {
        printf("Error allocating memory");
        exit(-1);
    }
}


/******************************************************************************
 * OpenFile
 *
 * Arguments: name - pointer the name of the file to open
 *            mode - pointer to the mode to use when opening file
 * Returns: pointer to the opened file; exits if given file cannot be opened with given mode
 *
 *****************************************************************************/

FILE * OpenFile ( char *name, char *mode )
{
    FILE *fp;
    fp = fopen ( name, mode );
    if (fp == NULL) {
        printf ("ERROR: It is not possible to open file %s!\n", name);
        exit (-1);
    }
    return (fp);
}

/******************************************************************************
 * MapInit
 *
 * Arguments: mapconfig - pointer the name of the file already opened and that we're going to process
 *
 * Returns: pointer to the opened file; exits if given file cannot be opened with given mode
 *
 *****************************************************************************/

ParkingLot * MapInit( FILE* mapconfig )
{

    int i;
    int col, row, floors, entries, accesses;
    ParkingLot* parkinglot; /*Pointer to struct */

    if (fscanf(mapconfig, "%d %d %d %d %d\n", &col, &row, &floors, &entries, &accesses) != 5)  /*If it can't read the 5 dimensions needed it exits the program*/
    {
        printf("Error reading map info.");
        exit(-1);
    }

    parkinglot = InitParkingLot(mapconfig, col, row, floors, accesses); /*Creates pointer to the parking lot*/

    return (parkinglot);
}


/******************************************************************************
 * MAIN
 *****************************************************************************/

int main( int argc, char *argv[])
{
    FILE* mapconfig, *mapinfo, *mapres; /*variables to the files being opened*/
    char* name = argv[1];
    ParkingLot* parkinglot; /*Pointer to the parkinglot struct */


    /*Verify number of arguments*/
    /*if(argc != 4)
    {
        printf("Wrong number of arguments. Must be of the form './gestor parque.cfg parque.inp [parque.res]'");
        exit(-1);
    }*/

    /*Open the first file - Parking Lot Description*/
    mapconfig = OpenFile ( name, "r" );

    /*Treat the data in the description file*/
    parkinglot = MapInit(mapconfig);

    /* Closes the file we were reading the map from*/
    fclose(mapconfig);


    return 0;
}
