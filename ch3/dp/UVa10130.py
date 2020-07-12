import sys
from functools import lru_cache

sys.setrecursionlimit(100000)

MAX_N = 1010
MAX_W = 40

N = 0
V = [0] * MAX_N
W = [0] * MAX_N

@lru_cache(maxsize=None)
def dp(pid, remW):
  if pid == N or remW == 0:
    return 0
  if W[pid] > remW:
    return dp(pid+1, remW)
  return max(dp(pid+1, remW), V[pid]+dp(pid+1, remW-W[pid]))


if __name__ == '__main__':
  T = int(input())
  for _ in range(T):
    dp.cache_clear()
    N = int(input())
    for i in range(N):
      V[i], W[i] = map(int, input().split())
    ans = 0
    G = int(input())
    for _ in range(G):
      MW = int(input())
      ans += dp(0, MW)
    print(ans)
