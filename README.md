# Comptool-MPLS-IP

As a final project for my university class CMPE 151: Advanced Computer Networks, we were told to give a presentation on a topic of our choosing, as long as it had not been previously discussed in class. I chose MPLS because it has interesting features like bandwidth reservation and traffic engineering, which are often glossed over in networking discussions.

During my research, I often came across the claim that MPLS forwarding is faster than traditional IP routing. Here, I present my testing of this claim and other information I have learned in the process.

## The case for MPLS

The intuition behind this claim has to do with the computational complexity of IP routing versus MPLS forwarding. In IP routing, a routing table is used to determine the exit interface for a given packet. This routing table consists of a list of networks, defined by an address and netmask. If a packet matches multiple networks, then the one with the larger netmask is favored. This process is iterative, as it needs to allow for partial matches and overlapping networks.

In MPLS, labels are matched exactly in a lookup table. This process is not iterative, and can be performed in constant time with the use of a hash table.

Asymptotic growth rates are an excellent way of judging the quality of an algorithm. In my implementation of IP routing lookups, I chose to use a Radix-2 Tree. Here is a side-by-side comparison of the two data structures:

Data Structure | Avg. Lookup   | Avg. Insert |Avg. Delete  | Worst Lookup | Worst Insert | Worst Delete 
-------------  | ------------- | ----------- | ----------- | ------------ | ------------ | ------------
Radix-2 Trie   | O(k)          |  O(k)       | O(k)        | O(k)         | O(k)         | O(k)
Hash Table     | O(1)          |  O(1)       | O(1)        | O(n)         | O(n)         | O(n)

Where k is the length of the key, and n is the number of key-value pairs in the data structure.

## Implementation

For the sake of analysis, I have greatly simplified the MPLS and IP lookup algorithms. Real implementations are much more complex and may have optimizations for increased performance, but are much more difficult to analyze.

Secondly, there is a semantic issue that needs to be cleared up. I have called my IP lookup data structure a Radix-2 trie. This may not be totally accurate, as some deinitions of a radix trie require that it be space-optimized and not store intermediate nodes. However I would not consider it to be a simple trie either, as it is a special case that has 2 children per node and compares strings bit-by-bit. Regardless, the implementation details for both data structures are as follows.

#### Radix-2 Trie

This trie implementation is quite simple, consisting of nodes with pointers to their children.
```cpp
struct treeNode{
    treeNode* zeroPtr;
    treeNode* onePtr;
    int outInterface;
};
```
Each treeNode also has an outInterface field. This field is set to the exit interface for a given route, or zero to indicate null. During a route lookup, a variable is used to store the current next hop interface. If a non-zero outInterface is encountered while traversing the trie, the varaible is overwritten with the value of outInterface. This allows the most precise exit interface to be selected even if there are multiple overlapping routes.

#### Jenkins Hash Table

The hash table I am using is the standard C++ std::unordered_map, with a custom Jenkins Hash function instead of the standard std::hash. I chose the Jenkins Hash function because it appears in the BGP portion of the source code for Quagga, a software routing suite. Although Quagga does not have an implementation for MPLS yet, I decided to use the Jenkins Hash function since it has already been tested and used in a networking context. It is a relatively simple hash function relying on bitwise operators, and can process 32-bit keys. Source code can be found in jhash.cpp.

Unordered_map resolves collisions by chaining. If two elements hash to the same value, they are placed in the same bucket. When one of these items is looked up, the key of the requested item is compared to the keys of all items in a given bucket. This process is what allows unordered_map to reach linear time in the worst case.

This solution has a decent (constant) lookup time, but is not very memory efficient. Both the keys and the values need to be stored for every entry.

//A more complicated yet memory-efficient solution may be to use a different hash algorithm such as Cuckoo Hashing.

## Results

The compiled program CompTool simulates a set of random lookups on the populated data structures. It records the average time of each lookup for a given number of routes, and outputs that data to a text file. The data is then plotted using Python's matplotlib library. The data below was generated using the following parameters:

Initial number of routes: 50

Number of random lookups per iteration: 50

Number of routes increased each iteration: 20

Final number of routes: 500,000

Here, average lookup time (in nanoseconds) is plotted against the number of routes in the data structure.

![alt-text](https://github.com/bradleypuckett/Comptool-MPLS-IP/blob/master/Images/rtree500k.png)

This plot shows the lookup times using the Radix Tree data structure. It has an undoubtably logarithmic shape, like other tree based data structures usually have.

At first glance however, this doesnt fit the O(k) runtime that was stated earlier. The important thing to remember here is that this is a plot of the *average* time over 50 random lookups.

//Statistically speaking

Therefore the average number of nodes traversed is directly related to the number of nodes present in the tree.

Given that our lookup strings are a maximum of 32 bits, there exists an upper bound in the case that there is a /32 route for every IPv4 address. That would produce the longest average lookup time since each lookup must perform 32 dereferences.


![alt text](https://github.com/bradleypuckett/Comptool-MPLS-IP/blob/master/Images/jhash500k.png "Jenkins Hash w/500k routes")

This plot shows the lookup times using the Jenkins Hash Table data structure. It is also interesting, in that it appears to run in linear time, rather than the expected constant time.  


![alt-text](https://github.com/bradleypuckett/Comptool-MPLS-IP/blob/master/Images/jhash500k-linreg.png)

Placing a line of best fit on the plot further confirms the linear shape. I conjecture that this linear behavior of Jenkins Hash is due to the collision resolution of std::unordered_map. This could be avoided by using a better hash scheme such as Cuckoo hashing, which resolves collisions in such a way to have constant time lookups in the worst case. There are a number of Cuckoo hash variants, so benchmarking each of these may yield some interesting results.

Another interesting point is that there seems to be an inverse relationship between hashing time and rate of collision. The simpler the hash algorithm is, the faster it can produce hashes. On the flipside, simple hash algorithms tend to have more collisions, which can tend towards O(n) rather than the desired O(1). Thus in an MPLS-like scenario where lookup time is critical, it is important to consider both the hash speed and collision rate when choosing an algorithm.


![alt-text](https://github.com/bradleypuckett/Comptool-MPLS-IP/blob/master/Images/jhash-loadfactor.png)

To see if the collision resolution of std::unordered_map is the culprit, I plotted the hash table's load factor side-by-side with the Jenkins Hash results.


## Final notes and conclusion

Modern hardware routers have ASICs and content addressable memory to help reduce the cost of routing lookups. Because of this, forwarding speed is not much of an advantage in MPLS. However there are a few things that may make exact-match lookups, like what is used in MPLS, attractive in the future.

First, technological infrastructure is moving more and more towards virtualization and the cloud.

Finally, the transition to IPv6 means that the iterative lookup process of IP forwarding will now be processing 128-bit addresses, as opposed to the 32-bit addresses of IPv4. Currently, the address block allocation for ISP customers is in debate. Address block sizes of /64, /56, and /48 are being considered. Due to this, IPv6-capable routers may have to lookup a maximum of 80-bit bitstrings.
