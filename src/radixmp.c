/*************************************************************\
|-------------------------------------------------------------|
|         Created by Ericson "Fogo" Soares on 25/03/17        |
|-------------------------------------------------------------|
|                 https://github.com/fogodev                  |
|-------------------------------------------------------------|
\*************************************************************/

#include "../include/radixmp.h"

void ompLsdRadixSort32bits(size_t size, unsigned* data, int numThreads)
{
    unsigned* buffer = (unsigned*) malloc(size * sizeof(unsigned));
    if(!buffer){
        fprintf(stderr,"Not enough memory to allocate buffer, you need %luGB\n", size * sizeof(unsigned));
        exit(1);
    }
    unsigned* temp;
    int bitsCount = sizeof(unsigned) * BITS;
    
    for (int shift = 0; shift < bitsCount; shift += BITS) {
        size_t buckets[BUCKETS] = {0};
        size_t localBuckets[BUCKETS] = {0};
        
        #pragma omp parallel firstprivate(localBuckets) num_threads(numThreads)
        {
            #pragma omp for schedule(static) nowait
            for (size_t numberIndex = 0; numberIndex < size; ++numberIndex)
                ++localBuckets[GET_BYTE(data[numberIndex], shift)];
            
            #pragma omp critical
            for (size_t bucketIndex = 0; bucketIndex < BUCKETS; ++bucketIndex)
                buckets[bucketIndex] += localBuckets[bucketIndex];
            
            #pragma omp barrier
            #pragma omp single
            for (size_t bucketIndex = 1; bucketIndex < BUCKETS; ++bucketIndex)
                buckets[bucketIndex] += buckets[bucketIndex - 1];
            
            int threadId = omp_get_thread_num();
            for (int currentThread = numThreads - 1; currentThread >= 0; --currentThread) {
                if (currentThread == threadId) {
                    for (size_t bucketIndex = 0; bucketIndex < BUCKETS; ++bucketIndex) {
                        buckets[bucketIndex] -= localBuckets[bucketIndex];
                        localBuckets[bucketIndex] = buckets[bucketIndex];
                    }
                } else {
                    #pragma omp barrier
                }
            }
            
            #pragma omp for schedule(static)
            for (size_t numberIndex = 0; numberIndex < size; ++numberIndex) {
                buffer[localBuckets[GET_BYTE(data[numberIndex], shift)]++] = data[numberIndex];
            }
        }
        
        temp = data;
        data = buffer;
        buffer = temp;
    }
    free(buffer);
}

void ompLsdRadixSort64bits(size_t size, unsigned long long* data, int numThreads)
{
    unsigned long long* buffer = (unsigned long long*) malloc(size * sizeof(unsigned long long));
    if(!buffer){
        fprintf(stderr,"Not enough memory to allocate buffer, you need %luGB\n", size * sizeof(unsigned long long));
        exit(1);
    }
    unsigned long long* temp;
    int bitsCount = sizeof(unsigned long long) * BITS;
    
    for (int shift = 0; shift < bitsCount; shift += BITS) {
        size_t buckets[BUCKETS] = {0};
        size_t localBuckets[BUCKETS] = {0};
        
        #pragma omp parallel firstprivate(localBuckets) num_threads(numThreads)
        {
            #pragma omp for schedule(static) nowait
            for (size_t numberIndex = 0; numberIndex < size; ++numberIndex)
                ++localBuckets[GET_BYTE(data[numberIndex], shift)];
            
            #pragma omp critical
            for (size_t bucketIndex = 0; bucketIndex < BUCKETS; ++bucketIndex)
                buckets[bucketIndex] += localBuckets[bucketIndex];
            
            #pragma omp barrier
            #pragma omp single
            for (size_t bucketIndex = 1; bucketIndex < BUCKETS; ++bucketIndex)
                buckets[bucketIndex] += buckets[bucketIndex - 1];
            
            int threadId = omp_get_thread_num();
            for (int currentThread = numThreads - 1; currentThread >= 0; --currentThread) {
                if (currentThread == threadId) {
                    for (size_t bucketIndex = 0; bucketIndex < BUCKETS; ++bucketIndex) {
                        buckets[bucketIndex] -= localBuckets[bucketIndex];
                        localBuckets[bucketIndex] = buckets[bucketIndex];
                    }
                } else {
                    #pragma omp barrier
                }
            }
            #pragma omp for schedule(static)
            for (size_t numberIndex = 0; numberIndex < size; ++numberIndex) {
                buffer[localBuckets[GET_BYTE(data[numberIndex], shift)]++] = data[numberIndex];
            }
        }
        
        temp = data;
        data = buffer;
        buffer = temp;
    }
    free(buffer);
}