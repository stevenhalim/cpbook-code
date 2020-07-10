''' UVa 10003 -- python solution

    O(N^2)
    Knuth-Yao optimization is used in this solution

    O(N^3) solution gets TLE in UVa as it is too slow for python despite of N <= 50
    It seems there is a lot of cases in the input
'''

import sys

if __name__ == '__main__':
  for line in sys.stdin:
    l = int(line.strip('\n'))
    if l == 0:
      break
    n = int(sys.stdin.readline().strip('\n'))
    A = [0] + list(map(int, sys.stdin.readline().strip('\n').split())) + [l]

    opt = [[0] * (n+3) for _ in range(n+3)]
    cut = [[10**9] * (n+2) for _ in range(n+2)]
    for i in range(1,n+2):
      cut[i-1][i] = 0
      opt[i-1][i] = i
    for i in range(n+1, -1, -1):
      for j in range(i, n+2):
        for k in range(opt[i][j-1], opt[i+1][j]+1):   # knuth-yao optimization
          res = cut[i][k]+cut[k][j]+A[j]-A[i]
          if res < cut[i][j]:
            cut[i][j] = res
            opt[i][j] = k

    print("The minimum cutting is %d." % cut[0][n+1])
