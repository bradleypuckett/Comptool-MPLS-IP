#include <cstddef>
#include <iostream>
#include <functional>
#include <random>
#include <unordered_map>
#include <utility>

#include <assert.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtree.h"
#include "IPUtils.h"
#include "jhash.h"
#include "RandomPermute.h"

std::pair<double, double> jhash_test(int arrSize, int sampleSize){

    assert(arrSize >= sampleSize);

    //Create new unordered_map using jenkins hash function
    std::unordered_map<uint32_t, int, std::function<decltype(jenkins_hash)>> ids(100, jenkins_hash );

    //Create sequential flow ID array [1,2,3,4,5...]
    //Create random output interface array [5,5,1,3,6,53]
    uint32_t mpls_arr1[arrSize];
    int mpls_arr2[arrSize];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for(int v = 0; v < arrSize; v++){
        mpls_arr1[v] = v + 1;
        mpls_arr2[v] = dis(gen);
    }
    
    //Add arrays to unordered_map
    for(int x = 0; x < arrSize; x++){
        ids[mpls_arr1[x]] = mpls_arr2[x];
    }

    //Shuffle flow id array and random array
    KnuthShuffleParallel(mpls_arr1, mpls_arr2, arrSize);

    int temp[sampleSize];
    double totalTime = 0.0;

    for(int y = 0; y < sampleSize; y++){

        timespec ts1;
        timespec ts2;
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts1);

        temp[y] = ids[mpls_arr1[y]];

        clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);

        totalTime += ((ts2.tv_sec > ts1.tv_sec) ? (ts2.tv_nsec + (1000000000 - ts1.tv_nsec)) : (ts2.tv_nsec - ts1.tv_nsec));
    }

    //Average results
    double avgTime = totalTime / ((double) sampleSize);
    std::pair<double, double> retVal = std::make_pair(avgTime, ids.load_factor());
    return retVal;
}

double rtree_test(int arrSize, int sampleSize){

    assert(arrSize >= sampleSize);

    //Create new tree using rtree nodes, root node is given default route 1
    treeNode * root = new treeNode(1);
    
    //Generate random interface numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    
    //Add random subnet and interface to tree
    for(int x = 0; x < arrSize; x++){
        int * randSub = generateRandomSubnet();
        root->add_subnet(randSub, dis(gen));
        delete[] randSub;
    }

    //Lookup random addresses in structure and average times
    int temp[sampleSize];
    double totalTime = 0.0;

    for(int y = 0; y < sampleSize; y++){

        timespec ts1;
        timespec ts2;
        int * randAddr = generateRandomAddress();

        clock_gettime(CLOCK_MONOTONIC_RAW, &ts1);

        temp[y] = root->lookup_address(randAddr);

        clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);

        delete[] randAddr;

        totalTime += ((ts2.tv_sec > ts1.tv_sec) ? (ts2.tv_nsec + (1000000000 - ts1.tv_nsec)) : (ts2.tv_nsec - ts1.tv_nsec));
    }

    //Average results
    double avgTime = totalTime / ((double) sampleSize);

    delete root;

    return avgTime;

}

int main(){

    int sampleSize = 50;
    int incrementSize = 20;
    int startSize = 50;
    int endSize = 500000;

    FILE* output1 = fopen("jhash.data", "w");
    FILE* output2 = fopen("rtree.data", "w");


    for(int x = startSize; x <= endSize; x += incrementSize){
        std::pair<double, double> result = jhash_test(x, sampleSize);
        fprintf(output1, "%d %f %f\n", x, result.first, result.second);
        fprintf(output2, "%d %f\n", x, rtree_test(x, sampleSize));
        printf("\rProgress: %d/%d", x, endSize);
    }
    std::cout << "\n" << std::endl; 

    fclose(output1);
    fclose(output2);
    return 0;
}