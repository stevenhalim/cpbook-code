import time, random

MAX_N = 200010


def naiveMatching(T, P):
  n = len(T)
  m = len(P)

  freq = 0
  for i in range(n):
    found = True
    for j in range(m):
      if not found:
        break
      if i+j >= n or P[j] != T[i+j]:
        found = False
    if found:
      freq += 1
  return freq


b = [0] * MAX_N

def kmpPreprocess(P):
  global b

  m = len(P)

  i, j = 0, -1
  b[0] = -1
  while i < m:
    while j >= 0 and P[i] != P[j]:
      j = b[j]
    i += 1
    j += 1
    b[i] = j


def kmpSearch(T, P):
  global b

  n = len(T)
  m = len(P)

  freq = 0
  i, j = 0, 0
  while i < n:
    while j >= 0 and T[i] != P[j]:
      j = b[j]
    i += 1
    j += 1
    if j == m:
      freq += 1
      j = b[j]
  return freq


p = 131
M = 10**9+7
Pow = [0] * MAX_N
h = [0] * MAX_N

def computeRollingHash(T):
  n = len(T)

  Pow[0] = 1
  for i in range(1, n):
    Pow[i] = (Pow[i-1]*p) % M
  h[0] = 0
  for i in range(n):
    if i != 0:
      h[i] = h[i-1];
    h[i] = (h[i] + (ord(T[i])*Pow[i]) % M) % M


def extEuclid(a, b):
  xx, yy = 0, 1
  x, y = 1, 0
  while b != 0:
    q = a//b
    a, b = b, a%b
    x, xx = xx, x-q*xx
    y, yy = yy, y-q*yy
  return a, x, y


def modInverse(b, m):
  d, x, y = extEuclid(b, m)
  if d != 1:
    return -1
  return (x+m)%m


def hash_fast(L, R):
  if L == 0:
    return h[R]
  ans = ((h[R] - h[L-1]) % M + M) % M
  ans = (ans * modInverse(Pow[L], M)) % M
  return ans


def main():
  extreme_limit = 100000
  letters = ['A', 'B']
  T = ''.join([random.choice(letters) for _ in range(extreme_limit-1)]) + 'B'
  P = ''.join([random.choice(letters) for _ in range(10)])
  n = len(T)
  m = len(P)

  time.clock()
  freq = 0
  pos = T.find(P, 0)
  while pos != -1:
    freq += 1
    pos = T.find(P, pos+1)
  print('String Library, #match = %d' % freq)
  print('Runtime =', time.clock(), 's')

  time.clock()
  print('Naive Matching, #match = %d' % naiveMatching(T, P))
  print('Runtime =', time.clock(), 's')
  
  time.clock()
  computeRollingHash(T)
  hP = 0;
  for i in range(m):
    hP = (hP + ord(P[i])*Pow[i]) % M
  freq = 0
  for i in range(n-m+1):
    if hash_fast(i, i+m-1) == hP:
      freq += 1
  print('Rabin-Karp, #match = %d' % freq)
  print('Runtime =', time.clock(), 's')

  time.clock()
  kmpPreprocess(P)
  print('Knuth-Morris-Pratt, #match = %d' % kmpSearch(T, P))
  print('Runtime =', time.clock(), 's')


main()
