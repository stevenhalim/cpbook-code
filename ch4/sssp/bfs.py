from collections import deque

p = []

def printPath(u):
    if p[u] == -1:
        print("{}".format(u), end="")
        return
    printPath(p[u])
    print(" {}".format(u), end="")

def main():
    INF = int(1e9)

    # Graph in Figure 4.3, format: list of unweighted edges
    # This example shows another form of reading graph input
    # 13 16
    # 0 1    1 2    2  3   0  4   1  5   2  6    3  7   5  6
    # 4 8    8 9    5 10   6 11   7 12   9 10   10 11  11 12

    f = open("bfs_in.txt", "r")

    V, E = map(int, f.readline().split())
    AL = [[] for u in range(V)]
    for _ in range(E):
        token = f.readline().split()
        for i in range(0, len(token), 2):
            AL[int(token[i])].append((int(token[i+1]), 0))
            AL[int(token[i+1])].append((int(token[i]), 0))

    # as an example, we start from this source, see Figure 4.3
    s = 5

    # BFS routine inside main() -- we do not use recursion
    dist = [INF for u in range(V)]
    dist[s] = 0
    q = deque()
    q.append(s)
    global p
    p = [-1 for u in range(V)]              # p is global

    layer = -1                              # for output printing
    isBipartite = True                      # additional feature

    while (len(q) > 0):
        u = q.popleft()
        if (dist[u] != layer): print("\nLayer {}: ".format(dist[u]), end = "")
        layer = dist[u]
        print("visit {}, ".format(u), end = "")
        for v, w in AL[u]:                  # w ignored
            if dist[v] == INF:
                dist[v] = dist[u]+1         # dist[v] != INF now
                p[v] = u                    # parent of v is u
                q.append(v)                 # for next iteration
            elif dist[v]%2 == dist[u]%2:    # same parity
                isBipartite = False

    print("\nShortest path: ", end = "")
    printPath(7)
    print("\nisBipartite? {}".format(isBipartite))

main()
