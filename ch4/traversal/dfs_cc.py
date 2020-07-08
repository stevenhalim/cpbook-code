import sys
from enum import Enum

class flag(Enum):
  UNVISITED = -1
  VISITED = -2

AL = []
dfs_num = []

def dfs(u):
  global AL
  global dfs_num

  sys.stdout.write(' '+str(u))
  dfs_num[u] = flag.VISITED.value
  for v, w in AL[u]:
    if dfs_num[v] == flag.UNVISITED.value:
      dfs(v)


def main():
  global AL
  global dfs_num

  fp = open('dfs_cc_in.txt', 'r')

  V = int(fp.readline().strip())
  AL = [[] for _ in range(V)]
  for u in range(V):
    tkn = list(map(int, fp.readline().strip().split()))
    k = tkn[0]
    for i in range(k):
      v, w = tkn[2*i+1], tkn[2*i+2]
      AL[u].append((v, w))

  print('Standard DFS Demo (the input graph must be UNDIRECTED)')
  dfs_num = [flag.UNVISITED.value] * V
  numCC = 0
  for u in range(V):
    if dfs_num[u] == flag.UNVISITED.value:
      numCC += 1
      sys.stdout.write('CC %d:' % numCC)
      dfs(u)
      sys.stdout.write('\n')
  print('There are %d connected components' % numCC);


main()
