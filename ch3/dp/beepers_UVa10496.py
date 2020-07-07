import sys,math
from functools import lru_cache
sys.setrecursionlimit(5000)

def LSOne(S):
    return ((S) & -(S))

def main():
    TC = int(input())
    for _ in range(TC):
        input()                                  # these two values: xsize ysize are not used
        x = [0]*11
        y = [0]*11
        x[0],y[0] = map(int, input().split())
        n = int(input())
        n += 1                                   # include Karel
        for i in range(1, n):                    # Karel is at index 0
            x[i],y[i] = map(int, input().split())
        dist = [[0] * n for _ in range(n)]       # Karel + max 10 beepers
        for i in range(n-1):                     # build distance table
            for j in range(i+1, n):
                dist[i][j] = dist[j][i] = abs(x[i]-x[j]) + abs(y[i]-y[j]) # Manhattan distance

        @lru_cache(maxsize=None)
        def dp(u, mask):                         # mask = free coordinates
            if mask == 0: return dist[u][0]      # close the loop
            ans = 2000000000
            m = mask
            while (m):                           # up to O(n)
                two_pow_v = LSOne(m)             # but this is fast
                v = int(math.log2(two_pow_v))+1  # offset v by +1
                ans = min(ans, dist[u][v] + dp(v, mask^two_pow_v)) # keep the min
                m -= two_pow_v
            return ans

        print(dp(0, (1<<(n-1))-1))         # DP-TSP
        # print("The shortest path has length {}".format(dp(0, (1<<(n-1))-1))) # DP-TSP

main()
