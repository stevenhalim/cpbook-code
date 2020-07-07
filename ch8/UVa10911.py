import sys, math
from functools import lru_cache
sys.setrecursionlimit(5000)

def LSOne(S):
    return ((S) & -(S))                          # important speedup

def main():
    caseNo = 0
    while True:
        N = int(input())                         # max N = 8
        if N == 0: break
        x = [0]*20
        y = [0]*20
        for i in range(2*N):
            dummy,x[i],y[i] = input().split()
            x[i] = int(x[i])
            y[i] = int(y[i])
        dist = [[0.0] * (2*N) for _ in range(2*N)]
        for i in range(2*N-1):                   # build distance table
            for j in range(i+1, 2*N):            # use `hypot' function
                dist[i][j] = dist[j][i] = math.hypot(x[i]-x[j], y[i]-y[j])

        @lru_cache(maxsize=None)
        def dp(mask):                            # DP state = mask
            if mask == 0: return 0               # all have been matched
            ans = 1e9                            # init with a large value
            two_pow_p1 = LSOne(mask)             # speedup
            p1 = int(math.log2(two_pow_p1))      # p1 is first on bit
            m = mask-two_pow_p1                  # turn off bit p1
            while m:
                two_pow_p2 = LSOne(m);           # then, try to match p1
                p2 = int(math.log2(two_pow_p2))  # with another on bit p2
                ans = min(ans, dist[p1][p2] + dp(mask^two_pow_p1^two_pow_p2))
                m -= two_pow_p2                  # turn off bit p2
            return ans

        caseNo += 1
        print("Case {}: {:.2f}".format(caseNo, dp((1<<(2*N)) - 1)))

main()
