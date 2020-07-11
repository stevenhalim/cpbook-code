import sys

UNVISITED = -1

dfsNumberCounter = 0
numSCC = 0
AL = []
AL_T = []
dfs_num = []
dfs_low = []
S = []
visited = []
st = []

def tarjanSCC(u):
  global dfs_low, dfs_num, dfsNumberCounter, visited
  global AL, numSCC, st

  dfs_low[u] = dfs_num[u] = dfsNumberCounter
  dfsNumberCounter += 1
  st.append(u)
  visited[u] = True
  for v, w in AL[u]:
    if dfs_num[v] == UNVISITED:
      tarjanSCC(v)
    if visited[v]:
      dfs_low[u] = min(dfs_low[u], dfs_low[v])

  if dfs_low[u] == dfs_num[u]:
    numSCC += 1
    while True:
      v = st[-1]
      st.pop()
      visited[v] = False
      if u == v:
        break


def Kosaraju(u, npass):
  global dfs_num, AL, AL_T, S

  dfs_num[u] = 1
  neighbour = AL[u] if npass == 1 else AL_T[u]
  for v, w in neighbour:
    if dfs_num[v] == UNVISITED:
      Kosaraju(v, npass)
  S.append(u)


if __name__ == '__main__':
  for line in sys.stdin:
    N, M = map(int, line.strip('\n').split())
    if N == 0 and M == 0:
      break
    AL = [list() for _ in range(N)]
    AL_T = [list() for _ in range(N)]
    for _ in range(M):
      V, W, P = map(int, sys.stdin.readline().strip('\n').split())
      V -= 1
      W -= 1
      AL[V].append([W, 1])
      AL_T[W].append([V, 1])
      if P == 2:
        AL[W].append([V, 1])
        AL_T[V].append([W, 1])

    ''' run Tarjan's SCC code here '''
    dfs_num = [UNVISITED] * N
    dfs_low = [0] * N
    visited = [False] * N
    st = []
    dfsNumberCounter = 0
    numSCC = 0
    for u in range(N):
      if dfs_num[u] == UNVISITED:
        tarjanSCC(u)

    ''' run Kosaraju's SCC code here '''
    # S = []
    # dfs_num = [UNVISITED] * N
    # for u in range(N):
    #   if dfs_num[u] == UNVISITED:
    #     Kosaraju(u, 1)
    # numSCC = 0
    # dfs_num = [UNVISITED] * N
    # for i in range(N-1, -1, -1):
    #   if dfs_num[S[i]] == UNVISITED:
    #     numSCC += 1
    #     Kosaraju(S[i], 2)

    print(1 if numSCC == 1 else 0)
