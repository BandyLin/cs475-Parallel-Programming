#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NUMT 1
#define NUM 2

struct s {
    float value;
    int pad[NUM];
} Array[4];

void fixOne() {
    omp_set_num_threads( NUMT );
    int someBigNumber = 1000000000;
    double time2 = omp_get_wtime();
    #pragma omp parallel for
    for( int i = 0; i < 4; i++ ) {
        for( int j = 0; j < someBigNumber; j++ ) {
            Array[ i ].value = Array[ i ].value + 2;
        }
    }
    
    double time1 = omp_get_wtime();
    // print performance here:::
    std::cout << "Number of Threads: " << NUMT << " Padding: " << NUM << " Time: " << time1-time2 << " Some Big Number: " << someBigNumber << "\n";
}

void fixTwo() {
    omp_set_num_threads( NUMT );
    int someBigNumber = 1000000000;
    double time2 = omp_get_wtime();
    #pragma omp parallel for
    for( int i = 0; i < 4; i++ ) {
        float index = Array[i].value;
        for( int j = 0; j < someBigNumber; j++ ) {
            index += 2;
        }
        Array[i].value = index;
    }
    
    double time1 = omp_get_wtime();
    // print performance here:::
    std::cout << "Number of Threads: " << NUMT << " Padding: " << NUM << " Time: " << time1-time2 << " Some Big Number: " << someBigNumber << "\n";
}

int main( int argc, char *argv[ ] ) {
#ifndef _OPENMP
    fprintf( stderr, "OpenMP is not available\n" );
    return 1;
#endif
    //Comment out which ever one you don't want to run
    fixOne();
    fixTwo();
    return 0;
}

