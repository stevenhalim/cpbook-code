import sys

N = 0
AL = []

def hierholzer(s):
  global AL, N

  ans = []
  idx = [0] * N
  st = [s]

  while len(st) != 0:
    u = st[-1]
    if idx[u] < len(AL[u]):
      st.append(AL[u][idx[u]])
      idx[u] += 1
    else:
      ans.append(u)
      st.pop()

  ans = ans[::-1]
  return ans


def main():
  global AL, N

  N = 7
  AL = [list() for _ in range(N)]
  AL[0] = [1, 6]
  AL[1] = [2]
  AL[2] = [3, 4]
  AL[3] = [0]
  AL[4] = [5]
  AL[5] = [0, 2]
  AL[6] = [5]

  ans = hierholzer(0)

  for u in ans:
    sys.stdout.write(str(chr(ord('A')+u))+' ')
  sys.stdout.write('\n')


main()
