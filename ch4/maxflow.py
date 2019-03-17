# Disclaimer: This code is a hybrid between old CP1-2-3 implementation of
# Edmonds Karp's algorithm -- re-written in OOP fashion and the fast
# Dinic's algorithm implementation by
# https://github.com/jaehyunp/stanfordacm/blob/master/code/Dinic.cc

from collections import deque

class max_flow:
	def __init__(self, _V):
		self.V = _V
		self.EL = []
		self.AL = [[] for i in range(self.V)]
		self.d = []
		self.last = []
		self.p = []

	def BFS(self, s, t):        # BFS to find augmenting path in residual graph
		self.d = [-1 for i in range(self.V)]
		self.d[s] = 0
		q = deque()
		q.append(s)
		self.p = [(-1, -1) for i in range(self.V)]      # record BFS sp tree
		while len(q) > 0:
			u = q.popleft()
			if (u == t):                                # stop as sink t reached
				break
			for idx in self.AL[u]:                      # explore neighbors of u
				also_u, v, cap, flow = self.EL[idx]     # stored in EL[idx]
				if cap-flow > 0 and self.d[v] == -1:    # positive residual edge
					self.d[v] = self.d[u]+1
					q.append(v)
					self.p[v] = (u, idx)
		return not self.d[t] == -1                      # has an augmenting path

	def send_one_flow(self, s, t, f = int(1e18)):       # send one flow from s->t
		if (s == t):                                    # bottleneck edge f found
			return f
		u, idx = self.p[t]
		also_u, v, cap, flow = self.EL[idx]
		pushed = self.send_one_flow(s, u, min(f, cap-flow))
		flow += pushed
		ru, rv, rcap, rflow = self.EL[idx^1]             # back edge
		rflow -= pushed                                  # back flow
		return pushed

	def DFS(self, s, t, f = int(1e18)):                        # traverse from s->t
		if s == t or f == 0:
			return f
		for i in range(self.last[s], len(self.AL[s])):   # remember last edge
			u, v, cap, flow = self.EL[self.AL[s][i]]
			if self.d[v] == self.d[u]+1:                 # in current layer graph
				pushed = self.DFS(v, t, min(f, cap-flow))
				if (pushed):
					flow += pushed
					ru, rv, rcap, rflow = self.EL[self.AL[s][i]^1]  # back edge
					rflow -= pushed
					return pushed
		return 0

	# if you are adding a bidirectional edge u<->v with weight w into your
	# flow graph, set directed = false (default value is directed = true)
	def add_edge(self, u, v, w, directed = True):
		if (u == v):                                      	# safeguard: no self loop
			return
		self.EL.append((u, v, w, 0))                      	# u->v, cap w, flow 0
		self.AL[u].append(len(self.EL)-1)                   # remember this index
		self.EL.append((v, u, 0 if directed else w, 0)) 	# back edge
		self.AL[v].append(len(self.EL)-1)                	# remember this index

	def edmonds_karp(self, s, t):
		mf = 0                                   			# mf stands for max_flow
		while (self.BFS(s, t)):                          	# an O(VE^2) EK algorithm
			f = self.send_one_flow(s, t)                	# find and send 1 flow f
			if (f == 0): 
				break                         				# if f == 0, stop
			mf += f                                   		# if f > 0, add to mf
		return mf

	def dinic(self, s, t):
		mf = 0                                   			# mf stands for max_flow
		while (self.BFS(s, t)):                          	# an O(VE^2) EK algorithm
			self.last = [0 for i in range(self.V)]
			f = self.DFS(s, t)                         		# important speedup
			while (f):	                   					# exhaust blocking flow
				mf += f
				f = self.DFS(s, t)
		return mf

def main():

	# Graph in Figure 4.24
	# 4 0 3
	# 2 2 3 1 7
	# 2 2 1 3 2
	# 1 3 7
	# 0

	f = open("maxflow_in.txt", "r")

	V, s, t = map(int, f.readline().split(" "))
	mf = max_flow(V)
	for u in range(V):
		x = f.readline().split(" ")
		k = int(x[0])
		for i in range(k):
			v, w = int(x[2*i+1]), int(x[2*i+2])
		mf.add_edge(u, v, w)                      			# default: directed edge

	#print("{}".format(mf.edmonds_karp(s, t)))
	print("{}".format(mf.dinic(s, t)))

main()