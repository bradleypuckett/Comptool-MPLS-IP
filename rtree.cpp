#include "rtree.h"

    treeNode::treeNode(int interface){
        zeroPtr = nullptr;
        onePtr = nullptr;
        outInterface = interface;
    }

    treeNode::~treeNode(){
        if(this->zeroPtr != nullptr){
            delete this->zeroPtr;
        }
        if(this->onePtr != nullptr){
            delete this->onePtr;
        }
    }

    void treeNode::add_subnet(int * subnet, int interface){
        treeNode * currentNode = this;

        for(int x = 1; x <= subnet[0]; x++){
            if(subnet[x] == 0){
                if(currentNode->zeroPtr == nullptr){
                    treeNode * newNode = new treeNode(0);
                    currentNode->zeroPtr = newNode;
                }
                currentNode = currentNode->zeroPtr;
            }

            else{
                if(currentNode->onePtr == nullptr){
                    treeNode * newNode = new treeNode(0);
                    currentNode->onePtr = newNode;
                }
                currentNode = currentNode->onePtr;
            }
        }
        
        currentNode->outInterface = interface;
        return;
    }

    void treeNode::printTree(){
        if(this->zeroPtr != nullptr){
            this->zeroPtr->printTree();
        }
        printf("At %p, Zero: %p, One: %p, Interface: %d\n", this, this->zeroPtr, this->onePtr, this->outInterface);
        if(this->onePtr != nullptr){
            this->onePtr->printTree();  
        }
        return;
    }

    int treeNode::lookup_address(int * address){

        int destination_int;
        treeNode * currentNode = this;

        for(int i = 0; i < 32; i++){
            if(currentNode->outInterface != 0){
                destination_int = currentNode->outInterface;
            }
            if(address[i] == 0){
                if(currentNode->zeroPtr == nullptr){
                    return destination_int;
                }
                else{
                    currentNode = currentNode->zeroPtr;
                }
            }
            else{
                if(currentNode->onePtr == nullptr){
                    return destination_int;
                }
                else{
                    currentNode = currentNode->onePtr;
                }
            }
        }
        return destination_int;
    }