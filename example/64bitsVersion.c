#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "../include/radixmp.h"

#define MAX_NUMBERS 1024 * 1024 * 512
#define NUM_THREADS 8

int main(int argc, char** argv)
{
    unsigned long long* numbers = malloc(MAX_NUMBERS * sizeof(unsigned long long));
    if(!numbers){
        fprintf(stderr,"Not enough memory to allocate numbers, you need %luGB\n", MAX_NUMBERS * sizeof(unsigned long long));
        exit(1);
    }
    
    srand(time(NULL));
    for (size_t numberIndex = 0; numberIndex < MAX_NUMBERS; ++numberIndex)
        numbers[numberIndex] = (unsigned) (rand() % 900000) + 100000;
    
    if(MAX_NUMBERS <= 1024){ // For testing reasons
        for (size_t numberIndex = 0; numberIndex < MAX_NUMBERS; ++numberIndex)
            printf("%llu ", numbers[numberIndex]);
        printf("\n");
    }
    
    printf(" \n\n\n\n Starting sort \n\n\n\n");
    
    double start = omp_get_wtime();
    ompLsdRadixSort64bits(MAX_NUMBERS, numbers, NUM_THREADS);
    double end = omp_get_wtime();
    
    printf("Elapsed time = %lf\n\n", end - start);
    
    if(MAX_NUMBERS <= 1024){ // For testing reasons
        for (size_t numberIndex = 0; numberIndex < MAX_NUMBERS; ++numberIndex)
            printf("%llu ", numbers[numberIndex]);
        printf("\n");
    }
    
    free(numbers);
    
    return 0;
}