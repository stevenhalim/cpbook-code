'''
the algorithm is similar to CPP,
but the output is stored in table
to avoid repeated call of floodfill
'''

import sys, copy

sys.setrecursionlimit(100000)

line = ['.'] * 150
grid = ['.' * 150] * 150
R = 0
C = 0

dr = (1, 1, 0,-1,-1,-1, 0, 1)
dc = (0, 1, 1, 1, 0,-1,-1,-1)

visited = []

def floodfill(r, c, c1, c2):
  global grid, visited

  ans = 1
  grid[r][c] = c2
  visited.append((r, c))
  for d in range(8):
    if 0 <= r+dr[d] < R and 0 <= c+dc[d] < C and grid[r+dr[d]][c+dc[d]] == c1:
      ans += floodfill(r+dr[d], c+dc[d], c1, c2)
  return ans

if __name__ == '__main__':
  TC = int(input())
  input()

  for tc in range(TC):
    R = 0
    while True:
      grid[R] = list(input())
      if grid[R][0] != 'L' and grid[R][0] != 'W':
        break
      R += 1
    C = len(grid[0])

    output = {}

    line = ''.join(grid[R])
    while True:
      row, col = map(int, line.split())
      row -= 1
      col -= 1

      if (row, col) not in output:
        visited = []
        ans = floodfill(row, col, 'W', '.')
        for cell in visited:
          output[cell] = ans

      print(output[(row, col)])

      try:
        line = input()
        if line == '':
          break
      except:
        break

    if tc < TC-1:
      print()
