import math

class SparseTable:
  def __init__(self, A=[]):
    self.A = A
    self.P2 = []
    self.L2 = []
    self.SpT = []

    n = len(self.A)
    L2_n = int(math.log2(n)) + 1
    self.P2 = [0] * (L2_n+1)
    self.L2 = [0] * (2**L2_n+1)
    for i in range(L2_n+1):
      self.P2[i] = 2**i
      self.L2[2**i] = i
    for i in range(2, self.P2[L2_n]):
      if self.L2[i] == 0:
        self.L2[i] = self.L2[i-1]

    self.SpT = [[None] * n for _ in range(self.L2[n]+1)]
    for j in range(n):
      self.SpT[0][j] = j

    for i in range(1, L2_n+1):
      for j in range(n-self.P2[i]+1):
        x = self.SpT[i-1][j]
        y = self.SpT[i-1][j+self.P2[i-1]]
        self.SpT[i][j] = x if A[x] <= A[y] else y

  def RMQ(self, i, j):
    k = self.L2[j-i+1]
    x = self.SpT[k][i]
    y = self.SpT[k][j-self.P2[k]+1]
    return x if self.A[x] <= self.A[y] else y


def main():
  A = [18, 17, 13, 19, 15, 11, 20]
  SpT = SparseTable(A)
  n = len(A)
  for i in range(n):
    for j in range(i, n):
      print('RMQ(%d, %d) = %d' % (i, j, SpT.RMQ(i,j)))


main()
