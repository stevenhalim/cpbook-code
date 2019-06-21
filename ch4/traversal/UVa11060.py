from heapq import heappush, heappop
import sys

# Beverages

def main():
	caseNo = 1
	while (True):
		AL = []
		mapper = {}
		reverseMapper = {}
		try:
			N = int(input())
		except:
			break
		for i in range(0, N):
			B1 = input()
			mapper[B1] = i
			reverseMapper[i] = B1
			AL.append([])

		in_degree = [0 for i in range(110)]
		M = int(input())
		for i in range(M):
			B1, B2 = input().split(" ")
			a = mapper[B1]
			b = mapper[B2]
			AL[a].append(b)
			in_degree[b] += 1

		sys.stdout.write("Case #{}: Dilbert should drink beverages in this order:".format(caseNo))
		caseNo += 1

		# enqueue vertices with zero incoming degree into a (priority) queue pq
		pq = []                                      # min priority queue
		for u in range(N):
			if in_degree[u] == 0: # all vertices with 0 in-degree can be processed
				heappush(pq, u)                          # smaller index goes first

		while (len(pq) > 0):                         # Kahn's algorithm
			u = heappop(pq)
			sys.stdout.write(" "+reverseMapper[u])
			for v in AL[u]:                            # process u
				in_degree[v] -= 1                        # virtually 'remove' u->v
				if in_degree[v] == 0:                    # v is the next candidate
					heappush(pq, v)                        # smallest id to front

		print(".\n");
		try:
			input()
		except:
			break
main()