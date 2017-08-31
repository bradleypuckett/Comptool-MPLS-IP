#ifndef _IP_UTILS_H
#define _IP_UTILS_H

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Generates a random subnet and stores result in array
   First integer specifies mask, and remaining integers
   specify all bits leading up to the mask length. So if
   the netmask was /23, then the function would return an
   array with 24 elements. The first would hold the number
   23, and the rest would either be 1 or 0 to represent
   the bit pattern of the address.                      */

int* generateRandomSubnet();

int* generateRandomAddress();

#endif
