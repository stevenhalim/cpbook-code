import sys

MOD = 1

def mod(a, m):
  return (a%m+m)%m

def matMul(a, b):
  global MOD

  ans = [[0, 0], [0, 0]]
  for i in range(2):
    for k in range(2):
      if a[i][k] == 0:
        continue
      for j in range(2):
        ans[i][j] += mod(a[i][k], MOD) * mod(b[k][j], MOD)
        ans[i][j] = mod(ans[i][j], MOD)
  return ans

def matPow(base, p):
  ans = [[1, 0], [0, 1]]
  while p != 0:
    if p&1 != 0:
      ans = matMul(ans, base)
    base = matMul(base, base)
    p >>= 1
  return ans


if __name__ == '__main__':
  for line in sys.stdin:
    n, m = map(int, line.strip('\n').split())
    MOD = 2**m
    ans = matPow([[1, 1], [1, 0]], n)
    print(ans[0][1])
