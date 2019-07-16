from collections import deque

def main():
    INF = int(1e9)

    f = open("bellman_ford_in.txt", "r")

    V, E, s = map(int, f.readline().split(" "))
    AL = [[] for u in range(V)]
    for _ in range(E):
        u, v, w = map(int, f.readline().split(" "))
        AL[u].append((v, w))

    # SPFA from source S
    # initially, only source vertex s has dist[s] = 0 and in the queue
    dist = [INF for u in range(V)]
    dist[s] = 0
    q = deque()
    q.append(s)
    in_queue = [0 for u in range(V)]
    in_queue[s] = 1
    while (len(q) > 0):
        u = q.popleft()                          # pop from queue
        in_queue[u] = 0
        for v, w in AL[u]:
            if (dist[u]+w >= dist[v]): continue  # not improving, skip
            dist[v] = dist[u]+w                  # relax operation
            if not in_queue[v]:                  # add to the queue
                q.append(v)                      # only if v is not
                in_queue[v] = 1                  # already in the queue

    for u in range(V):
        print("SSSP({}, {}) = {}".format(s, u, dist[u]))

main()
