#ifndef _RANDOM_PERMUTE_H
#define _RANDOM_PERMUTE_H

#include <random>

void KnuthShuffle(int * arr, size_t arr_len);

void KnuthShuffleParallel(uint32_t * arr1, int * arr2, size_t arr1_len);

#endif
