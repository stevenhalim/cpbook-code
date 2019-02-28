from heapq import heappush, heappop
from collections import deque

def main():
	INF = int(1e9)
	TC = int(input())
	for caseNo in range(1, TC+1):
		V, E, s, t = map(int, input().split(" "))
		AL = [[] for i in range(V)] # build graph
		for i in range(E):
			a, b, w = map(int, input().split(" "))
			AL[a].append((b, w))
			AL[b].append((a, w))


		# # Dijkstra from source s
		# dist = [INF for i in range(V)]
		# dist[s] = 0
		# pq = []
		# heappush(pq, (0, s))
		# while (len(pq) > 0):
		# 	d, u = heappop(pq)
		# 	if not d == dist[u]:
		# 		continue
		# 	for v, w in AL[u]:
		# 		if (dist[u] + w < dist[v]):
		# 			dist[v] = dist[u] + w
		# 			heappush(pq, (dist[v], v))

		# SPFA from source S
		# initially, only source vertex s has dist[s] = 0 and in the queue
		dist = [INF for i in range(V)]
		dist[s] = 0
		q = deque()
		q.append(s)
		in_queue = [0 for i in range(V)]
		in_queue[s] = 1
		while (len(q) > 0):
			u = q.popleft() # pop from queue
			in_queue[u] = 0
			for v, w in AL[u]: # all outgoing edges from u
				if (dist[u] + w < dist[v]): # if can relax
					dist[v] = dist[u] + w # relax
					if (not in_queue[v]): # add to the queue
						q.append(v) # only if it's not in the queue
						in_queue[v] = 1

		print ("Case #{}: {}".format(caseNo, dist[t] if not dist[t] == INF else "unreachable"))

main()