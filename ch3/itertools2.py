import itertools
items = [1, 2, 3, 4]
N = len(items)
combi = []
for i in range(1, N+1):
    combi = combi+list(itertools.combinations(items, i))
for stuffs in combi:
    print(stuffs)
