from heapq import heappush, heappop

# Union-Find Disjoint Sets Library written in OOP manner
# using both path compression and union by rank heuristics
class UnionFind:                                # OOP style
    def __init__(self, N):
        self.p = [i for i in range(N)]
        self.rank = [0 for i in range(N)]
        self.setSize = [1 for i in range(N)]
        self.numSets = N

    def findSet(self, i):
        if (self.p[i] == i):
            return i
        else:
            self.p[i] = self.findSet(self.p[i])
            return self.p[i]

    def isSameSet(self, i, j):
        return self.findSet(i) == self.findSet(j)

    def unionSet(self, i, j):
        if (not self.isSameSet(i, j)):
            self.numSets -= 1
            x = self.findSet(i)
            y = self.findSet(j)
        # rank is used to keep the tree short
        if (self.rank[x] > self.rank[y]):
            self.p[y] = x
            self.setSize[x] += self.setSize[y]
        else:
            self.p[x] = y
            self.setSize[y] += self.setSize[x]
            if (self.rank[x] == self.rank[y]):
                self.rank[y] += 1

    def numDisjointSets(self):
        return self.numSets

    def sizeOfSet(self, i):
        return self.setSize[self.findSet(i)]

def main():
    # Graph in Figure 4.10 left, format: list of weighted edges
    # This example shows another form of reading graph input
    # 5 7
    # 0 1 4
    # 0 2 4
    # 0 3 6
    # 0 4 6
    # 1 2 2
    # 2 3 8
    # 3 4 9

    f = open("mst_in.txt", "r")

    V, E = map(int, f.readline().split(" "))
    # Kruskal's algorithm
    EL = []
    for i in range(E):
        u, v, w = map(int, f.readline().split(" ")) # read as (u, v, w)
        EL.append((w, u, v))                        # reorder as (w, u, v)
    EL.sort()                                       # sort by w, O(E log E)

    mst_cost = 0
    num_taken = 0
    UF = UnionFind(V)                               # all V are disjoint sets

    for i in range(E):                              # for each edge, O(E)
        if num_taken == V-1:
            break
        w, u, v = EL[i]
        if (not UF.isSameSet(u, v)):                # check
            num_taken += 1                          # 1 more edge is taken
            mst_cost += w                           # add w of this edge
            UF.unionSet(u, v)                       # link them
            # note: the runtime cost of UFDS is very light

    # note: the number of disjoint sets must eventually be 1 for a valid MST
    print("MST cost = {} (Kruskal's)".format(mst_cost))

main()
