import sys
from functools import lru_cache

sys.setrecursionlimit(1000000)

num = []
sign = []
S = set()

@lru_cache(maxsize=None)
def dp(open, n, value):
  global num, sign

  if n == len(num)-1:
    S.add(value)
    return

  nval = sign[n+1] * num[n+1] * (1 if open%2 == 0 else -1)
  if open > 0:
    dp(open-1, n+1, value+nval)
  if sign[n+1] == -1:
    dp(open+1, n+1, value+nval)
  dp(open, n+1, value+nval)


if __name__ == '__main__':
  for line in sys.stdin:
    tkn = line.strip('\n').split()

    sign = [1]
    num = [int(tkn[0])]
    for i in range(1, len(tkn), 2):
      sign.append(-1 if tkn[i] == '-' else 1)
      num.append(int(tkn[i+1]))

    S.clear()
    dp.cache_clear()
    dp(0, 0, num[0])
    print(len(S))
