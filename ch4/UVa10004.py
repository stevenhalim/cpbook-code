# Bicoloring

from collections import deque

def main():
    INF = int(1e9)
    while (True):
        n = int(input())
        if (n == 0):
            break
        AL = [[] for i in range(n)]
        
        l = int(input())
        for i in range(l):
            a, b = map(int, input().split(" "))
            AL[a].append(b)
            AL[b].append(a) # bidirectional

        s = 0
        q = deque()
        q.append(s)
        color = [INF for i in range(n)]
        color[s] = 0
        isBipartite = True         # add one more boolean flag, initially true
        while (len(q) > 0 and isBipartite):
            u = q.popleft()
            for v in AL[u]:
                if (color[v] == INF):    # but, instead of recording distance,
                    color[v] = 1 - color[u] # we just record two colors {0, 1}
                    q.append(v)
                elif (color[v] == color[u]):       # u & v have the same color
                    isBipartite = False          # we have a coloring conflict
                    break

        print("{}BICOLORABLE.".format("" if isBipartite else "NOT "))

main()