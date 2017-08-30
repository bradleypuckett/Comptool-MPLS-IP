# Comptool-MPLS-IP

As a final project for my university class CMPE 151: Advanced Computer Networks, we were told to give a presentation on a topic of our choosing, as long as it had not been previously discussed in class. I chose MPLS because it has interesting features like bandwidth reservation and traffic engineering, which are often glossed over in networking discussions.

During my research, I often came across the claim that MPLS forwarding is faster than traditional IP routing. Here, I present my testing of this claim and other information I have learned in the process.

## The case for MPLS

The intuition behind this claim has to do with the computational complexity of IP routing versus MPLS forwarding. In IP routing, a routing table is used to determine the exit interface for a given packet. This routing table consists of a list of networks, defined by an address and netmask. If a packet matches multiple networks, then the one with the larger netmask is favored. This process is iterative, as it needs to allow for partial matches and overlapping networks.

In MPLS, labels are matched exactly in a lookup table. This process is not iterative, and can be performed in constant time with the use of a hash table.

Asymptotic growth rates are an excellent way of judging the quality of an algorithm. In my implementation of IP routing lookups, I chose to use a Radix-2 Tree. Here is a side-by-side comparison of the two data structures:

 Data Structure      | Avg. Lookup   | Avg. Insert | Avg. Delete | Worst Lookup | Worst Insert | Worst Delete 
------------- | ------------- | ----------- | ----------- | ------------ | ------------ | ------------
Radix-2 Trie  | O(k)          |  O(k)       | O(k)        | O(k)         | O(k)         | O(k)
Hash Table    | O(1)          |  O(1)       | O(1)        | O(n)         | O(n)         | O(n)

Where k is the number of symbols in the key, and n is the number of key-value pairs in the data structure.

//The simpler the hash algorithm is, the faster packets can be forwarded using an MPLS-like system. On the flipside, simple hash algorithms tend to have more collisions, which can tend towards O(n) rather than the desired O(1).

## Implementation

//Greatly simplified for the sake of analysis, real implementations are much more complex and may have optimizations for increased performance
//Semantic concerns with radix tree vs patricia tree vs trie

## Results

//Basic image Jhash

//Basic image Rtree

//Jhash with linreg

//Jhash with load factor

//Conjecture that this linear behavior of jenkins hash is due to the collision resolution behavior of unordered_map. Could be avoided by using a better hash function such as Cuckoo hashing, or another perfect hash function. Each of these obviously suffer from their own issues such as longer hashing time, or other problems that make dynamic updates computationally expensive.


## Final notes and conclusion

Modern hardware routers have ASICs and content addressable memory to help reduce the cost of routing lookups. Because of this, forwarding speed is not much of an advantage in MPLS. However there are a few things that may make exact-match lookups, like what is used in MPLS, attractive in the future.

First, technological infrastructure is moving more and more towards virtualization and the cloud.

Finally, the transition to IPv6 means that the iterative lookup process of IP forwarding will now be processing 128-bit addresses, as opposed to the 32-bit addresses of IPv4. Currently, the address block allocation for ISP customers is in debate. Address block sizes of /64, /56, and /48 are being considered. Due to this, IPv6-capable routers may have to lookup a maximum of 80-bit bitstrings.

Simplify for the sake of hypothesis testing
