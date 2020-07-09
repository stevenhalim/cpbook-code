import sys

sys.setrecursionlimit(5000)

AL = []
par = []
heavy = []
group = []

def heavy_light(x):
  global AL, par, heavy

  size = 1
  max_child_size = 0
  for y in AL[x]:
    if y == par[x]:
      continue
    par[y] = x
    child_size = heavy_light(y)
    if child_size > max_child_size:
      max_child_size = child_size
      heavy[x] = y
    size += child_size
  return size

def decompose(x, p):
  global AL, par, heavy, group

  group[x] = p
  for y in AL[x]:
    if y == par[x]:
      continue
    if y == heavy[x]:
      decompose(y, p)
    else:
      decompose(y, y)


def main():
  global AL, par, heavy, group

  N = 19
  AL = [None] * N
  AL[0] = [1, 2, 3]
  AL[1] = [0, 4]
  AL[2] = [0, 5, 6, 7]
  AL[3] = [0, 8]
  AL[4] = [1, 9, 10]
  AL[5] = [2]
  AL[6] = [2]
  AL[7] = [2, 11, 12]
  AL[8] = [3]
  AL[9] = [4]
  AL[10] = [4, 13]
  AL[11] = [7, 14]
  AL[12] = [7, 15]
  AL[13] = [10]
  AL[14] = [11, 16]
  AL[15] = [12, 17, 18]
  AL[16] = [14]
  AL[17] = [15]
  AL[18] = [15]

  par = [-1] * N
  heavy = [-1] * N
  heavy_light(0)

  group = [-1] * N
  decompose(0, 0)

  for i in range(N):
    print('%2d, parent = %2d, heaviest child = %2d, belong to heavy-paths group = %d' % (i, par[i], heavy[i], group[i]))


main()
