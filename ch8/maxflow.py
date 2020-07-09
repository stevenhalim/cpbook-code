INF = 10**18

class max_flow:
  def __init__(self, V: int):
    self.V = V
    self.EL = []
    self.AL = [list() for _ in range(self.V)]
    self.d = []
    self.last = []
    self.p = []

  def BFS(self, s, t):
    self.d = [-1] * self.V
    self.d[s] = 0
    self.p = [[-1, -1] for _ in range(self.V)]
    q = [s]
    while len(q) != 0:
      u = q[0]
      q.pop(0)
      if u == t:
        break
      for idx in self.AL[u]:
        v, cap, flow = self.EL[idx]
        if cap-flow > 0 and self.d[v] == -1:
          self.d[v] = self.d[u]+1
          q.append(v)
          self.p[v] = [u, idx]
    return self.d[t] != -1

  def send_one_flow(self, s, t, f=INF):
    if s == t:
      return f
    u, idx = self.p[t]
    _, cap, flow = self.EL[idx]
    pushed = self.send_one_flow(s, u, min(f, cap-flow))
    flow += pushed
    self.EL[idx][2] = flow
    self.EL[idx^1][2] -= pushed
    return pushed

  def DFS(self, u, t, f=INF):
    if u == t or f == 0:
      return f
    for i in range(self.last[u], len(self.AL[u])):
      self.last[u] = i
      v, cap, flow = self.EL[self.AL[u][i]]
      if self.d[v] != self.d[u]+1:
        continue
      pushed = self.DFS(v, t, min(f, cap-flow))
      if pushed != 0:
        flow += pushed
        self.EL[self.AL[u][i]][2] = flow
        self.EL[self.AL[u][i]^1][2] -= pushed
        return pushed
    return 0

  def add_edge(self, u, v, w, directed=True):
    if u == v:
      return
    self.EL.append([v, w, 0])
    self.AL[u].append(len(self.EL)-1)
    self.EL.append([u, 0 if directed else w, 0])
    self.AL[v].append(len(self.EL)-1)

  def edmonds_karp(self, s, t):
    mf = 0
    while self.BFS(s, t):
      f = self.send_one_flow(s, t)
      if f == 0:
        break
      mf += f
    return mf

  def dinic(self, s, t):
    mf = 0
    while self.BFS(s, t):
      self.last = [0] * self.V
      f = self.DFS(s, t)
      while f != 0:
        mf += f
        f = self.DFS(s, t)
    return mf



def main():

  fp = open('maxflow_in.txt', 'r')

  V, s, t = map(int, fp.readline().strip().split())

  mf = max_flow(V)

  for u in range(V):
    tkn = list(map(int, fp.readline().strip().split()))
    k = tkn[0]
    for i in range(k):
      v, w = tkn[2*i+1], tkn[2*i+2]
      mf.add_edge(u, v, w)

  # print(mf.edmonds_karp(s, t))
  print(mf.dinic(s, t))


main()
