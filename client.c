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
    FILE* mapconfig, *carconfig, *resconfig; /*variables to the files being opened*/
    char* mapfile = argv[1];
    char* carfile = argv[2];
    char* restrictionsfile = argv[3];
    ParkingLot* parkinglot; /*Pointer to the parkinglot struct */
    ListNode * eventlist, * carlist;
    int vertices, timeunit = 0;
    Array decoder;
    
    
    /*Verify number of arguments*/
    if(argc != 4)
    {
        printf("Wrong number of arguments. Must be of the form './gestor parque.cfg parque.inp [parque.res]'");
        exit(-1);
    }
    
    /*Open the first file - Parking Lot Description*/
    mapconfig = OpenFile ( mapfile, "r" );
    
    /*Treat the data in the description file*/
    parkinglot = MapInit(mapconfig);
    
    /* Closes the file we were reading the map from*/
    fclose(mapconfig);
    
    /*Open the 2 other files - car info and the restrictions*/
    carconfig = OpenFile ( carfile, "r" );
    resconfig = OpenFile ( restrictionsfile, "r" );
    
    /*Treat the data in the car config file and the restriction file, initializing an eventlist (queue)*/
    eventlist = EventListInit( carconfig, resconfig );
    //PrintEventList(eventlist);
    
    /* Closes the file we were reading the map from*/
    fclose(carconfig);
    fclose(resconfig);
    
    /*Gets # of vertices and pointer to decoder for further use*/
    vertices = GetVertices(parkinglot);
    decoder = GetDecoder(parkinglot);
    
    /*Use the event list to make a list featuring the cars present in the park at time = 0*/
    carlist = CarListInit(eventlist, decoder, vertices);
    
    while(funcaoverificarseacabou)
    {
        ExecuteEvent(eventlist, &carlist, timeunit, decoder, vertices);
        
        mover quem tem de ser movido (cars com status = 1)
        
        temos de updatar o decoder para ter os carros estacionados <----
        
        timeunit ++;
    }
    
    return 0;
}
