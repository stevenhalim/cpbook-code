import random

def isprime(v):
    primes = [2,3,5,7,11,13,17,19,23,29]
    return (v in primes)

def Aug(L, vis, AL, match):     # return 1 if there exists an augmenting path from L
    if (vis[L]):                                                # return 0 otherwise
        return 0
    vis[L] = 1
    for R in AL[L]:
        if match[R] == -1 or Aug(match[R], vis, AL, match):
            match[R] = L
            return 1                                              # found 1 matching
    return 0                                                           # no matching

def main():
    # # build bipartite graph with directed edge from left to right set
    #
    # # Graph in Figure 4.40 can be built on the fly
    # # we know there are 6 vertices in this bipartite graph, left side are numbered 0,1,2, right side 3,4,5
    #
    # V = 6
    # Vleft = 3
    # set1 = [1,7,11]
    # set2 = [4,10,12]
    #
    # # Graph in Figure 4.41 can be built on the fly
    # # we know there are 5 vertices in this bipartite graph, left side are numbered 0,1, right side 3,4,5
    #
    # V = 5
    # Vleft = 2
    # set1 = [1,7]
    # set2 = [4,10,12]
    #
    # # build the bipartite graph, only directed edge from left to right is needed
    # AL = [[] for i in range(V)]
    # for i in range(Vleft):
    #   for j in range(3):
    #       if isprime(set1[i] + set2[j]):
    #           AL[i].append(3 + j)
    #
    # # For bipartite graph in Figure 4.44, V = 5, Vleft = 3 (vertex 0 unused)
    # AL = [[] for i in range(5)]
    # AL[0] = [] # dummy vertex, but you can choose to use this vertex
    # AL[1] = [3, 4]
    # AL[2] = [3]
    # AL[3] = [] # we use directed edges from left to right set only
    # AL[4] = []

    V = 5
    Vleft = 3
    AL = [[] for i in range(V)]
    AL[1].append(3)
    AL[1].append(4)
    AL[2].append(3)

    # build unweighted bipartite graph with directed edge left->right set
    freeV = set()
    for L in range(Vleft):
        freeV.add(L)            # assume all vertices on left set are free initially
    match = [-1 for i in range(V)]  # V is the number of vertices in bipartite graph
    MCBM = 0

    # Greedy pre-processing for trivial Augmenting Paths
    # try commenting versus un-commenting this for-loop
    for L in range(Vleft):                                                                     # O(V+E)
        candidates = []
        for R in AL[L]:
            candidates.append(R)
        if len(candidates) > 0:
            MCBM += 1
            freeV.remove(L)                                     # L is matched, no longer a free vertex
            a = random.randint(0, len(candidates)-1) % len(candidates) # randomize this greedy matching
            match[candidates[a]] = L

    for f in freeV:                                         # for each of the k remaining free vertices
        vis = [0 in range(Vleft)]                                         # reset before each recursion
        MCBM += Aug(f, vis, AL, match)                  # once f is matched, f remains matched till end

    print("Found {} matchings".format(MCBM))                          # the answer is 2 for Figure 4.42

main()