import sys
from functools import lru_cache
sys.setrecursionlimit(5000)

def main():                                       # easy to code
    TC = int(input())
    for _ in range(TC):
        M,C = map(int, input().split())
        price = [[] * 20 for _ in range(C)]
        for g in range(C):
            price[g] = list(map(int, input().split())) # store k in price[g][0]

        @lru_cache(maxsize=None)                  # built-in memoization
        def dp(g, money):
            if money < 0: return -1e9             # fail, return -ve number
            if g == C: return M-money             # we are done
            ans = -1                              # start with a -ve number
            for k in range(1, price[g][0]+1):     # try each model k
                ans = max(ans, dp(g+1, money-price[g][k]))
            return ans                            # TOP-DOWN: memoize ans

        if dp(0, M) < 0:                          # start the top-down DP
            print("no solution")
        else:
            print("{}".format(dp(0, M)))

main()
