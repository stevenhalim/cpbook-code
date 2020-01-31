import itertools
N = 7
items = list(range(1, N+1))
c = [list(itertools.combinations(items, i)) for i in range(1, N+1)]
c = list(itertools.chain(*c))                     # combine lists
print(len(c))                                     # should be 2^7-1 = 127
