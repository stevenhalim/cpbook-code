from bisect import bisect_left
i = bisect_left(L, v)
print(i != len(L) and L[i] == v)
