import sys
from functools import lru_cache

sys.setrecursionlimit(1000000)

AL = []
Children = []
vis = []

def dfs(u):
  global AL, Children, vis

  vis[u] = True
  for v in AL[u]:
    if not vis[v]:
      Children[u].append(v)
      dfs(v)

@lru_cache(maxsize=None)
def mvc(u, flag):
  global AL, Children

  if len(Children[u]) == 0:
    return flag
  elif flag == 0:
    return sum([mvc(v,1) for v in Children[u]])
  elif flag == 1:
    return 1+sum([min(mvc(v,1), mvc(v,0)) for v in Children[u]])


if __name__ == '__main__':
  for line in sys.stdin:
    N = int(line.strip('\n'))
    if N == 0:
      break
    AL = [list() for _ in range(N)]
    Children = [list() for _ in range(N)]
    for u in range(N):
      tkn = list(map(int, sys.stdin.readline().strip('\n').split()))
      ni = tkn[0]
      for i in range(1, ni+1):
        v = tkn[i]-1
        AL[u].append(v)
    if N == 1:
      print(1)
      continue
    vis = [False] * N
    dfs(0)
    mvc.cache_clear()
    print(min(mvc(0, 1), mvc(0, 0)))
