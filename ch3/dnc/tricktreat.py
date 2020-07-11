import sys, math

if __name__ == '__main__':
  for line in sys.stdin:
    n = int(line.strip('\n'))
    xs = [0] * n
    ys = [0] * n
    yq = [0] * n
    if n == 0:
      break
    for i in range(n):
      xs[i], ys[i] = map(float, sys.stdin.readline().strip('\n').split())
      yq[i] = ys[i]**2
    xs = tuple(xs)
    ys = tuple(ys)
    yq = tuple(yq)
    lo = min(xs)
    hi = max(xs)
    for i in range(50):
      delta = (hi-lo)/3.0
      m1 = lo+delta
      m2 = hi-delta

      ans_m1 = -1
      ans_m2 = -1
      for j in range(n):
        ans_m1 = max(ans_m1, (xs[j]-m1)**2 + yq[j])
        ans_m2 = max(ans_m2, (xs[j]-m2)**2 + yq[j])

      if ans_m1 > ans_m2:
        lo = m1
      else:
        hi = m2

    ans = -1
    for i in range(n):
      ans = max(ans, math.hypot(xs[i]-lo, ys[i]))

    print('%.10lf %.10lf' % (lo, ans))

    try:
      sys.stdin.readline()
    except:
      pass
