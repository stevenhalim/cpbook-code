from bisect import *

MAX_N = 100000

def reconstruct_print(end, a, p):
    x = end
    s = []
    while p[x] >= 0:
        s.append(a[x])
        x = p[x]
    s.append(a[x])
    print('[' + ', '.join(map(str, s[::-1])) + ']')

n = 11
A = [-7, 10, 9, 2, 3, 8, 8, 1, 2, 3, 4]

L = [None] * MAX_N
L_id = [None] * MAX_N
P = [None] * MAX_N
lis = lis_end = 0
for i in range(n):
    pos = bisect_left(L, A[i], 0, lis)
    L[pos] = A[i]
    L_id[pos] = i
    P[i] = L_id[pos-1] if pos else -1
    if pos+1 > lis:
        lis = pos+1
        lis_end = i
    print('Considering element A[{}] = {}'.format(i, A[i]))
    print('LIS ending at A[{}] is of length {}: '.format(i, pos+1), end='')
    reconstruct_print(i, A, P)
    print('L is now: [' + ', '.join(map(str, L[:lis])) + ']\n')
print('Final LIS is of length {}: '.format(lis), end='')
reconstruct_print(lis_end, A, P)
