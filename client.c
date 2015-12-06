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
        exit(0);
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
    int col, row, floors, entries, accesses;
    ParkingLot* parkinglot; /*Pointer to struct */

    if (fscanf(mapconfig, "%d %d %d %d %d\n", &col, &row, &floors, &entries, &accesses) != 5)  /*If it can't read the 5 dimensions needed it exits the program*/
    {
        printf("Error reading map info.");
        exit(0);
    }

    parkinglot = InitParkingLot(mapconfig, col, row, floors, accesses); /*Creates pointer to the parking lot*/

    return (parkinglot);
}


/******************************************************************************
 * MAIN
 *****************************************************************************/

int main( int argc, char *argv[])
{
    FILE* mapconfig, *carconfig, *restconfig, *fpout; /*variables to the files being opened*/
    char*fileNameOut;
    char* mapfile = argv[1];
    char* carfile = argv[2];
    char* restfile = argv[3];
    ParkingLot* parkinglot; /*Pointer to the parkinglot struct */
    int i, timeunit = 0; /*Because we need to handle cars  */
    char * extOut = ".pts";
    int finalflag = 0;
    int restflag = 1;
    ListNode* resthead = ListInit();

    /*Verify number of arguments*/
    if(argc > 4 && argc < 3)
    {
        printf("Wrong number of arguments. Must be of the form './gestor parque.cfg parque.inp [parque.res]'");
        exit(0);
    }

    if(argc == 3)
        restflag = 0;

    /*Open the first file - Parking Lot Description*/
    mapconfig = OpenFile ( mapfile, "r" );

    /*Treat the data in the description file*/
    parkinglot = MapInit(mapconfig);

    /* Closes the file we were reading the map from*/
    fclose(mapconfig);

    /*Open the second file - Car info file*/
    carconfig = OpenFile ( carfile, "r" );

    /*Open the third file - restrictions config*/
    if(restflag == 1)
    {
        restconfig = OpenFile ( restfile, "r" );
        resthead = RestInit(restconfig);
    }

    OcuppyParkedCars(parkinglot, carconfig) ; /*Occupies the positions of the cars already parked when the time starts */

    rewind(carconfig);

     /* Determine output filename */
    fileNameOut = ( char* )malloc( ( strlen( argv[1] ) + 2 ) * sizeof( char ) );
    VerifyMalloc((Item) fileNameOut);
    if( fileNameOut == NULL ){
        printf("Memory allocation error for fileNameOut.\n" );
        exit(0);
    }
    strcpy( fileNameOut, argv[1] );
    for (i = 0; fileNameOut[i] != '.'; i++){}
    fileNameOut[i] = '\0';
    strcat(fileNameOut, extOut);
    /* Open output file */
    fpout  = OpenFile(fileNameOut, "w");
    /* Frees output file */
    free(fileNameOut);

    while (finalflag == 0)
    {
        finalflag = HandleCar(parkinglot, carconfig, fpout, timeunit);
        if(restflag == 1)
           resthead = HandleRest(resthead, parkinglot, timeunit, restconfig);

        timeunit++;
    }

    FreeParkingLot(parkinglot);

    fclose(carconfig);
    fclose(fpout);

    exit(0);
}
