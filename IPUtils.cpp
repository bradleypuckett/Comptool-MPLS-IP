#include "IPUtils.h"
#include <iostream>

using namespace std;

int* generateRandomSubnet(){
	int x = (rand() % 32) + 1;
	int * vals = new int[x + 1];
	vals[0] = x;
	for(int y = 1; y <= vals[0]; y++){
		vals[y] = rand() % 2;
	}
	return vals;
}

int* generateRandomAddress(){
	int * vals = new int[32];
	for(int x = 0; x < 32; x++){
		vals[x] = rand() % 2;
	}
	return vals;
}
