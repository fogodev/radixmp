/*************************************************************\
|-------------------------------------------------------------|
|         Created by Ericson "Fogo" Soares on 25/03/17        |
|-------------------------------------------------------------|
|                 https://github.com/fogodev                  |
|-------------------------------------------------------------|
\*************************************************************/

#ifndef RADIXMP_RADIXMP_H
#define RADIXMP_RADIXMP_H

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define BITS 8
#define BUCKETS (1 << BITS)
#define MASK (BUCKETS-1)
#define GET_BYTE(number, shift) (((number) >> shift) & MASK)

void ompLsdRadixSort32bits(size_t size, unsigned* data, int numThreads);
void ompLsdRadixSort64bits(size_t size, unsigned long long* data, int numThreads);

#endif //RADIXMP_RADIXMP_H
