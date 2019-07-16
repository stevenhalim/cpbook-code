from heapq import heappush, heappop

def main():
    INF = int(1e9)

    # Graph in Figure 4.17
    # 5 7 0
    # 0 1 2
    # 0 2 6
    # 0 3 7
    # 1 3 3
    # 1 4 6
    # 2 4 1
    # 3 4 5

    f = open("dijkstra_in.txt", "r")

    V, E, s = map(int, f.readline().split(" "))
    AL = [[] for u in range(V)]
    for _ in range(E):
        u, v, w = map(int, f.readline().split(" "))
        AL[u].append((v, w))                     # directed graph

    # (Modified) Dijkstra's routine
    dist = [INF for u in range(V)]
    dist[s] = 0
    pq = []
    heappush(pq, (0, s))

    # sort the pairs by non-decreasing distance from s
    while (len(pq) > 0):                    # main loop
        d, u = heappop(pq)                  # shortest unvisited u
        if (d > dist[u]): continue          # a very important check
        for v, w in AL[u]:                  # all edges from u
            if (dist[u]+w >= dist[v]): continue # not improving, skip
            dist[v] = dist[u]+w             # relax operation
            heappush(pq, (dist[v], v))  

    for u in range(V):
        print("SSSP({}, {}) = {}".format(s, u, dist[u]))

main()
