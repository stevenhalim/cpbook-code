def main():
	INF = int(1e9)
	MAX_V = 450 # if |V| > 450, you cannot use Floyd Washall's

	AM = [[INF for j in range(MAX_V)] for i in range(MAX_V)]

	# Graph in Figure 4.30
	# 5 9
	# 0 1 2
	# 0 2 1
	# 0 4 3
	# 1 3 4
	# 2 1 1
	# 2 4 1
	# 3 0 1
	# 3 2 3
	# 3 4 5

	f = open("floyd_warshall_in.txt", "r")
	V, E = map(int, f.readline().split(" "))
	for u in range(V):
		AM[u][u] = 0

	for i in range(E):
		u, v, w = map(int, f.readline().split(" "))
		AM[u][v] = w 	# directed graph

	for k in range(V):	# loop order is k->u->v
		for u in range(V):
			for v in range(V):
				AM[u][v] = min(AM[u][v], AM[u][k] + AM[k][v])

	for u in range(V):
		for v in range(V):
			print("APSP({}, {}) = {}".format(u, v, AM[u][v]))

main()