import sys

MAX_N = 1000

children = []
L = [0] * (2*MAX_N)
E = [0] * (2*MAX_N)
H = [0] * (2*MAX_N)
idx = 0

def dfs(cur, depth):
  global children, L, E, H, idx

  H[cur] = idx
  E[idx] = cur
  L[idx] = depth
  idx += 1
  for nxt in children[cur]:
    dfs(nxt, depth+1)
    E[idx] = cur
    L[idx] = depth
    idx += 1

def buildRMQ():
  global idx, H, MAX_N

  idx = 0
  H = [-1] * (2*MAX_N)
  dfs(0, 0)


def main():
  global children,  H, E, L

  children = [list() for _ in range(10)]
  children[0] = [1, 7]
  children[1] = [2, 3, 6]
  children[3] = [4, 5]
  children[7] = [8, 9]

  buildRMQ()
  print(' '.join([str(H[i]) for i in range(2*10-1)]))
  print(' '.join([str(E[i]) for i in range(2*10-1)]))
  print(' '.join([str(L[i]) for i in range(2*10-1)]))


main()
