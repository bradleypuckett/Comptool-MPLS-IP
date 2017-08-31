#ifndef __RTREE_H__
#define __RTREE_H__

#include <cstddef>

#include <stdio.h>


struct treeNode{
	treeNode* zeroPtr;
	treeNode* onePtr;
	int outInterface;

	treeNode(int interface);
	~treeNode();

    void add_subnet(int * subnet, int interface);
	void printTree();
	int lookup_address(int * address);
};

#endif
