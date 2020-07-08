import sys
from enum import Enum

class flag(Enum):
  UNVISITED = -1
  EXPLORED = -2
  VISITED = -3

AL = []
dfs_num = []
dfs_parent = []

def cycleCheck(u):
  global AL
  global dfs_num
  global dfs_parent

  dfs_num[u] = flag.EXPLORED.value
  for v, w in AL[u]:
    if dfs_num[v] == flag.UNVISITED.value:
      dfs_parent[v] = u
      cycleCheck(v)
    elif dfs_num[v] == flag.EXPLORED.value:
      if v == dfs_parent[u]:
        printf(' Bidirectional Edge (%d, %d)-(%d, %d)' % (u, v, v, u))
      else:
        print('Back Edge (%d, %d) (Cycle)' % (u, v))
  dfs_num[u] = flag.VISITED.value


def main():
  global AL
  global dfs_num
  global dfs_parent

  fp = open('scc_in.txt', 'r')

  V = int(fp.readline().strip())
  AL = [[] for _ in range(V)]
  for u in range(V):
    tkn = list(map(int, fp.readline().strip().split()))
    k = tkn[0]
    for i in range(k):
      v, w = [tkn[2*i+1], tkn[2*i+2]]
      AL[u].append((v, w))

  print('Graph Edges Property Check')
  dfs_num = [flag.UNVISITED.value] * V
  dfs_parent = [-1] * V
  for u in range(V):
    if dfs_num[u] == flag.UNVISITED.value:
      cycleCheck(u)


main()
