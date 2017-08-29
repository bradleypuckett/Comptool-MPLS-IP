# Comptool-MPLS-IP

As a final project for my university class CMPE 151: Advanced Computer Networks, we were told to give a presentation on a topic of our choosing, as long as it had not been previously discussed in class. I chose MPLS because it has interesting features like bandwidth reservation and traffic engineering, which are often glossed over in networking discussions.

During my research, I often came across the claim that MPLS forwarding is faster than traditional IP routing. Here, I present my testing of this claim and other information I have learned in the process.

## The case for MPLS

The intuition behind this claim has to do with the computational complexity of IP routing versus MPLS forwarding. In IP routing, a routing table is used to determine the exit interface for a given packet. This routing table consists of a list of networks, defined by an address and netmask. If a packet matches multiple networks, then the one with the larger netmask is favored. This process is iterative, as it needs to allow for partial matches and overlapping networks.

In MPLS, labels are matched exactly in a lookup table. This process is not iterative, and can be performed in constant time with the use of a hash table.

Asymptotic growth rates are an excellent way of judging the quality of an algorithm. In my implementation of IP routing lookups, I chose to use a Radix-2 Tree. Here is a side-by-side comparison of the various data structures:

Tree
Radix-2 Tree
Hash Table

## Implementation

## Results

## Final notes and conclusion

Cuckoo Hashing
IPv6
Simplify for the sake of hypothesis testing
