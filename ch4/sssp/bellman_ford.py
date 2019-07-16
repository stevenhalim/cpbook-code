def main():
    INF = int(1e9)

    # Graph in Figure 4.18, has negative weight, but no negative cycle
    # 5 5 0
    # 0 1 1
    # 0 2 10
    # 1 3 2
    # 2 3 -10
    # 3 4 3

    # Graph in Figure 4.19, negative cycle exists, Bellman Ford's can detect this
    # 3 3 0
    # 0 1 1000
    # 1 2 15
    # 2 1 -42

    f = open("bellman_ford_in.txt", "r")

    V, E, s = map(int, f.readline().split(" "))
    AL = [[] for u in range(V)]
    for _ in range(E):
        u, v, w = map(int, f.readline().split(" "))
        AL[u].append((v, w))

    # Bellman Ford's routine, basically = relax all E edges V-1 times
    dist = [INF for u in range(V)]               # INF = 1e9 here
    dist[s] = 0
    for i in range(0, V-1):                      # total O(V*E)
        modified = False                         # optimization
        for u in range(0, V):                    # these two loops = O(E)
            if (not dist[u] == INF):             # important check
                for v, w in AL[u]:
                    if (dist[u]+w >= dist[v]): continue # not improving, skip
                    dist[v] = dist[u]+w          # relax operation
                    modified = True              # optimization
        if (not modified): break                 # optimization

    hasNegativeCycle = False
    for u in range(0, V):                        # one more pass to check
        if (not dist[u] == INF):
            for v, w in AL[u]:
                if (dist[v] > dist[u] + w):      # should be false
                    hasNegativeCycle = True      # if true => -ve cycle
    print("Negative Cycle Exist? {}".format("Yes" if hasNegativeCycle else "No"))

    if (not hasNegativeCycle):
        for u in range(0, V):
            print("SSSP({}, {}) = {}".format(s, u, dist[u]))

main()
