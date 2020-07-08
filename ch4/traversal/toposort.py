import sys
from enum import Enum

class flag(Enum):
  UNVISITED = -1
  VISITED = -2

AL = []
dfs_num = []
ts = []

def toposort(u):
  global AL
  global dfs_num
  global ts

  dfs_num[u] = flag.VISITED.value
  for v, w in AL[u]:
    if dfs_num[v] == flag.UNVISITED.value:
      toposort(v)
  ts.append(u)


def main():
  global AL
  global dfs_num
  global ts

  fp = open('toposort_in.txt', 'r')

  V = int(fp.readline().strip())
  AL = [[] for _ in range(V)]
  for u in range(V):
    tkn = list(map(int, fp.readline().strip().split()))
    k = tkn[0]
    for i in range(k):
      v, w = tkn[2*i+1], tkn[2*i+2]
      AL[u].append((v, w))

  print('Topological Sort (the input graph must be DAG)')
  dfs_num = [flag.UNVISITED.value] * V
  for u in range(V):
    if dfs_num[u] == flag.UNVISITED.value:
      toposort(u)
  ts = ts[::-1]
  print(' '.join(map(str, ts)))


main()
