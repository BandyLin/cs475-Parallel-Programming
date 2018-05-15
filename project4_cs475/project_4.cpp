#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// starting date and time:
int    NowYear = 2017;        // 2017 - 2022
int    NowMonth = 0;        // 0 - 11

float    NowPrecip;        // inches of rain per month
float    NowTemp;        // temperature this month
// starting state (feel free to change this if you want):
float    NowHeight = 1.0;        // grain height in inches
int    NowNumDeer = 2;        // number of deer in the current population
int NowNumPredator = 1;         //number of predators in current population
unsigned int seed = 0;  // a thread-private variable

const float GRAIN_GROWS_PER_MONTH =        8.0;
const float ONE_PREDATOR_EATS_PER_MONTH = 1;
const float ONE_DEER_EATS_PER_MONTH =        0.5;

const float AVG_PRECIP_PER_MONTH =        6.0;    // average
const float AMP_PRECIP_PER_MONTH =        6.0;    // plus or minus
const float RANDOM_PRECIP =            2.0;    // plus or minus noise

const float AVG_TEMP =                50.0;    // average
const float AMP_TEMP =                20.0;    // plus or minus
const float RANDOM_TEMP =            10.0;    // plus or minus noise

const float MIDTEMP =                40.0;
const float MIDPRECIP =                10.0;

float SQR( float x ) {
    return x*x;
}

float Ranf( unsigned int *seedp,  float low, float high ) {
    float r = (float) rand_r( seedp );              // 0 - RAND_MAX
    
    return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

int Ranf( unsigned int *seedp, int ilow, int ihigh ) {
    float low = (float)ilow;
    float high = (float)ihigh + 0.9999f;
    
    return (int)(  Ranf(seedp, low,high) );
}
float x = Ranf( &seed, -1.f, 1.f );

void GrainDeer() {
    while( NowYear < 2023 )
    {
        // compute a temporary next-value for this quantity
        // based on the current state of the simulation:
        int deer = NowNumDeer;
        if (deer != NowHeight) {
            if (deer > NowHeight) {
                deer--;
            } else {
                deer++;
            }
        }
        
        // DoneComputing barrier:
        #pragma omp barrier
        NowNumDeer = deer;
        
        // DoneAssigning barrier:
        #pragma omp barrier
        
        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Grain(){
    while( NowYear < 2023 )
    {
        // compute a temporary next-value for this quantity
        // based on the current state of the simulation:
        float tempHeight = NowHeight;
        float tempFactor = exp(-SQR((NowTemp - MIDTEMP)/ 10.0));
        float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP)/ 10.0));
        tempHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        tempHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        if (tempHeight < 0) {
            tempHeight = 0;
        }
        // DoneComputing barrier:
        #pragma omp barrier
        NowHeight = tempHeight;
        
        // DoneAssigning barrier:
        #pragma omp barrier
        
        // DonePrinting barrier:
        #pragma omp barrier
    }
    
}

void Watcher() {
    while( NowYear < 2023 )
    {
        // compute a temporary next-value for this quantity
        // based on the current state of the simulation:
        
        // DoneComputing barrier:
        #pragma omp barrier
        
        // DoneAssigning barrier:
        #pragma omp barrier
        std::cout << "NowMounth: " << NowMonth << " NowYear: " << NowYear << " NowNumDeer: " << NowNumDeer << " NowPrecip: " << NowPrecip << " NowTemp: " << NowTemp << " NowHeight: " << NowHeight << " NowNumPredator: " << NowNumPredator << "\n";
        if(NowMonth == 11) {
            NowMonth = 0;
            NowYear++;
        } else {
            NowMonth++;
        }
        float ang = (30.0 * (float) NowMonth + 15.0) * (M_PI / 180.0);
        float temp = AVG_TEMP - AMP_TEMP * cos( ang );
        unsigned int seed = 0;
        NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP);
        
        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
        NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
        if( NowPrecip < 0. )
            NowPrecip = 0.;
        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Predator() {
    while( NowYear < 2023 )
    {
        // compute a temporary next-value for this quantity
        // based on the current state of the simulation:
        int hunts = Ranf(&seed,0,5);
        int deer = NowNumDeer;
        //Predator has 1/5 chance of hunting and killing a deer
        if (hunts == 1) {
            deer--;
        }
        
        // DoneComputing barrier:
        #pragma omp barrier
        NowNumDeer = deer;
        
        // DoneAssigning barrier:
        #pragma omp barrier

        
        // DonePrinting barrier:
        #pragma omp barrier

    }
}

int main( int argc, char *argv[ ] ) {
    #ifndef _OPENMP
        fprintf( stderr, "OpenMP is not available\n" );
        return 1;
    #endif
    
    omp_set_num_threads( 4 );    // same as # of sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            GrainDeer( );
        }
        
        #pragma omp section
        {
            Grain( );
        }
        
        #pragma omp section
        {
            Watcher( );
        }
        
        #pragma omp section
        {
            Predator( );    // your own
        }
    }       // implied barrier -- all functions must return in order
    // to allow any of them to get past here
    
    return 0;
}
