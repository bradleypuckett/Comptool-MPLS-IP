#include <iostream>
#include <ostream>
#include <random>
#include <string>

#include <assert.h>
#include <stdio.h>
#include <sys/time.h>

void KnuthShuffle(int * arr, size_t arr_len){

	std::random_device rd;
	std::mt19937 gen(rd());
	
	for (unsigned int x = 0; x < arr_len; x++){
        std::uniform_int_distribution<> dis(x, arr_len - 1);
		int a = dis(gen);

		int b = arr[a];
		arr[a] = arr[x];
		arr[x] = b;
	}
}

void KnuthShuffleParallel(uint32_t * arr1, int * arr2, size_t arr1_len){::

	std::random_device rd;
	std::mt19937 gen(rd());
	
	for (unsigned int x = 0; x < arr1_len; x++){
        std::uniform_int_distribution<> dis(x, arr1_len - 1);
		int a = dis(gen);

		uint32_t b = arr1[a];
		arr1[a] = arr1[x];
		arr1[x] = b;

		int c = arr2[a];
		arr2[a] = arr2[x];
		arr2[x] = c;
	}
}
