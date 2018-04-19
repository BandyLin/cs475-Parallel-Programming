#include <omp.h>
#include <stdio.h>
#include <math.h>

#define NUMT	         1
#define ARRAYSIZE       10000	// you decide
#define NUMTRIES        100	// you decide

float A[ARRAYSIZE];
float B[ARRAYSIZE];
float C[ARRAYSIZE];

float Height( int, int );

int main( int argc, char *argv[ ] )
{
    . . .
    
    // the area of a single full-sized tile:
    
    float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
                          ( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );
    
    // sum up the weighted heights into the variable "volume"
    // using an OpenMP for loop and a reduction:
    
    ?????
}
