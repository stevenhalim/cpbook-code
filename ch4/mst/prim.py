from heapq import heappush, heappop

def process(u, taken, AL, pq):                      # set u as taken and enqueue neighbors of u
    taken[u] = 1
    for v, w in AL[u]:
        if (not taken[v]):
            heappush(pq, (w, v))                    # sort by (inc) weight
                                                    # then by (inc) id

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
    # Prim's algorithm
    AL = [[] for i in range(V)]                     # the graph stored in AL
    for i in range(E):
        u, v, w = map(int, f.readline().split(" ")) # read as (u, v, w)
        AL[u].append((v, w))
        AL[v].append((u, w))

    taken = [0 for i in range(V)]                   # to avoid cycle, no vertex is taken
    pq = []                                         # to select shorter edges
    process(0, taken, AL, pq)                       # take+process vertex 0
    mst_cost = 0                                    # no edge has been taken
    num_taken = 0
    while len(pq) > 0 and num_taken < V-1:          # until we take V-1 edges
        w, u = heappop(pq)
        if not taken[u]:                            # we have not taken u yet
            num_taken += 1                          # 1 more edge is taken
            mst_cost += w                           # add w of this edge
            process(u, taken, AL, pq)               # take+process vertex u
                                                    # each edge is in pq once

    print("MST cost = {} (Prim's)".format(mst_cost))

main()
