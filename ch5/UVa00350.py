# Pseudo-Random Numbers, 0.288s in Java, 0.022s in C++, 0.160s in Python

Z = I = M = L = -1

def f(x):
	global Z, I, M, L
	return (Z * x + I) % M

def floydCycleFinding(x0):
	# 1st part: finding k*mu, hare's speed is 2x tortoise's
	tortoise = f(x0) # f(x0) is the node next to x0
	hare = f(f(x0))
	while (not tortoise == hare):
		tortoise = f(tortoise)
		hare = f(f(hare))

	# 2nd part: finding mu, hare and tortoise move at the same speed
	mu = 0
	hare = x0
	while (not tortoise == hare):
		tortoise = f(tortoise)
		hare = f(hare)
		mu += 1

	# 3rd part: finding lambda, hare moves, tortoise stays
	lambd = 1
	hare = f(tortoise)
	while (tortoise != hare):
		hare = f(hare)
		lambd += 1

	return lambd

def main():
	global Z, I, M, L
	Z, I, M, L = map(int, input().split(" "))
	case = 1
	while not Z == 0 and not I == 0 and not M == 0 and not L == 0:
		print("Case {}: {}".format(case, floydCycleFinding(L)))
		case += 1
		Z, I, M, L = map(int, input().split(" "))

main()