import random

def swap(A, i, j): 
    A[i],A[j] = A[j],A[i] 
    return A

def Partition(A, l, r):
    p = A[l]                                     # p is the pivot
    m = l                                        # S1 and S2 are empty
    for k in range(l+1, r+1):                    # explore unknown region
        if A[k] < p:                             # case 2
            m += 1
            swap(A, k, m)
        # notice that we do nothing in case 1: a[k] >= p
    swap(A, l, m)                                # swap pivot with a[m]
    return m                                     # return pivot index

def RandPartition(A, l, r):
    p = random.randint(l, r)                     # select a random pivot
    swap(A, l, p)                                # swap A[p] with A[l]
    return Partition(A, l, r)

def QuickSelect(A, l, r, k):                     # expected O(n)
    if l == r:
        return A[l]
    q = RandPartition(A, l, r)                   # O(n)
    if q+1 == k:
        return A[q]
    elif q+1 > k:
        return QuickSelect(A, l, q-1, k)
    else:
        return QuickSelect(A, q+1, r, k)

def main():
    A = [2, 8, 7, 1, 5, 4, 6, 3]                 # permutation of [1..8]

    print("{}".format(QuickSelect(A, 0, 7, 8)))  # the output must be 8
    print("{}".format(QuickSelect(A, 0, 7, 7)))  # the output must be 7
    print("{}".format(QuickSelect(A, 0, 7, 6)))  # the output must be 6
    print("{}".format(QuickSelect(A, 0, 7, 5)))  # the output must be 5
    print("{}".format(QuickSelect(A, 0, 7, 4)))  # the output must be 4
    print("{}".format(QuickSelect(A, 0, 7, 3)))  # the output must be 3
    print("{}".format(QuickSelect(A, 0, 7, 2)))  # the output must be 2
    print("{}".format(QuickSelect(A, 0, 7, 1)))  # the output must be 1

    # try experimenting with the content of array A to see the behavior of "QuickSelect"

main()
