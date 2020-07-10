import sys
from math import sqrt

EPS = 1e-9

class sp:
  def __init__(self):
    x, y = 0, 0
    x_l, x_r = 0.0, 0.0


if __name__ == '__main__':
  for line in sys.stdin:
    n, l, w = map(int, line.strip('\n').split())
    sprinkler = [sp() for _ in range(n)]
    for i in range(n):
      sprinkler[i].x, sprinkler[i].r = map(int, sys.stdin.readline().strip('\n').split())
      if 2*sprinkler[i].r >= w:
        d_x = sqrt(sprinkler[i].r*sprinkler[i].r - (w/2.0)*(w/2.0))
        sprinkler[i].x_l = sprinkler[i].x-d_x
        sprinkler[i].x_r = sprinkler[i].x+d_x
      else:
        sprinkler[i].x_l = sprinkler[i].x_r = sprinkler[i].x

    def cmp(a: sp):
      return a.x_l, -a.x_r
    sprinkler = sorted(sprinkler, key=cmp)
    possible = True
    covered = 0.0
    ans = 0
    skip = 0
    for i in range(n):
      if not possible:
        break
      if covered > l:
        break
      if i < skip:
        continue
      if sprinkler[i].x_r < covered+EPS:
        continue
      if sprinkler[i].x_l < covered+EPS:
        max_r = -1.0
        skip = i
        for j in range(i, n):
          if not (sprinkler[j].x_l < covered+EPS):
            break
          if sprinkler[j].x_r > max_r:
            max_r = sprinkler[j].x_r
            skip = j
        ans += 1
        covered = max_r
      else:
        possible = False

    if not possible or covered < l:
      print(-1)
    else:
      print(ans)
