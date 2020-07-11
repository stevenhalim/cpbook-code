import math

INF = 10**9
EPS = 1e-9

def DEG_to_RAD(d):
  return d*math.pi/180.0


def RAD_to_DEG(r):
  return r*180.0/math.pi


class point_i:
  def __init__(self, x=0, y=0):
    self.x = x
    self.y = y

class point:
  def __init__(self, x=0, y=0):
    self.x = x
    self.y = y

  def __lt__(self, other):
    return (self.x, self.y) < (other.x, other.y)

  def __eq__(self, other):
    return math.isclose(self.x, other.x) and math.isclose(self.y, other.y)


def dist(p1, p2):
  return math.hypot(p1.x-p2.x, p1.y-p2.y)


def rotate(p, theta):
  rad = DEG_to_RAD(theta)
  x = p.x * math.cos(rad) - p.y * math.sin(rad)
  y = p.x * math.sin(rad) + p.y * math.cos(rad)
  return point(x, y)


class line:
  def __init__(self):
    self.a = 0
    self.b = 0
    self.c = 0

def pointsToLine(p1, p2, l):
  if abs(p1.x - p2.x) < EPS:
    l.a, l.b, l.c = 1.0, 0.0, -p1.x
  else:
    a = -(p1.y - p2.y) / (p1.x - p2.x)
    l.a, l.b, l.c = a, 1.0, -(a * p1.x) - p1.y


class line2:
  def __init__(self):
    self.m = 0
    self.c = 0

def pointsToLine2(p1, p2, l):
  if p1.x == p2.x:
    l.m = INF
    l.c = p1.x
    return 0
  else:
    l.m = (p1.y - p2.y) / (p1.x - p2.x)
    l.c = p1.y - l.m * p1.x
    return 1


def areParallel(l1, l2):
  return math.isclose(l1.a, l2.a) and math.isclose(l1.b, l2.b)

def areSame(l1, l2):
  return areParallel(l1, l2) and math.isclose(l1.c, l2.c)


def areIntersect(l1, l2, p):
  if areParallel(l1, l2):
    return False
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b)
  if not math.isclose(l1.b, 0.0):
    p.y = -(l1.a * p.x + l1.c)
  else:
    p.y = -(l2.a * p.x + l2.c)
  return True


class vec:
  def __init__(self, x=0, y=0):
    self.x = x
    self.y = y

def toVec(a, b):
  return vec(b.x-a.x, b.y-a.y)

def scale(v, s):
  return vec(v.x*s, v.y*s)

def translate(p, v):
  return point(p.x+v.x, p.y+v.y)


def pointSlopeToLine(p, m, l):
  l.a, l.b = -m, 1
  l.c = -((l.a * p.x) + (l.b * p.y))


def closestPoint(l, p, ans):
  if math.isclose(l.b, 0.0):
    ans.x, ans.y = -l.c, p.y
    return
  if math.isclose(l.a, 0.0):
    ans.x, ans.y = p.x, -l.c
    return
  perpendicular = line()
  pointSlopeToLine(p, 1.0/l.a, perpendicular)
  areIntersect(l, perpendicular, ans)


def reflectionPoint(l, p, ans):
  b = point()
  closestPoint(l, p, b)
  v = toVec(p, b)
  ans.x, ans.y = p.x + 2 * v.x, p.y + 2 * v.y


def dot(a, b):
  return a.x * b.x + a.y * b.y

def norm_sq(v):
  return v.x * v.x + v.y * v.y

def angle(a, o, b):
  oa = toVec(o, a)
  ob = toVec(o, b)
  return  math.acos(dot(oa, ob) / math.sqrt(norm_sq(oa) * norm_sq(ob)))


def distToLine(p, a, b, c):
  ap = toVec(a, p)
  ab = toVec(a, b)
  u = dot(ap, ab) / norm_sq(ab)
  s = scale(ab, u)
  c.x, c.y = a.x+s.x, a.y+s.y
  return dist(p, c)


def distToLineSegment(p, a, b, c):
  ap = toVec(a, p)
  ab = toVec(a, b)
  u = dot(ap, ab) / norm_sq(ab)
  if u < 0.0:
    c.x, c.y = a.x, a.y
    return dist(p, a)
  if u > 1.0:
    c.x, c.y = b.x, b.y
    return dist(p, b)
  return distToLine(p, a, b, c)


def cross(a, b):
  return a.x * b.y - a.y * b.x


def ccw(p, q, r):
  return cross(toVec(p, q), toVec(p, r)) > -EPS


def collinear(p, q, r):
  return abs(cross(toVec(p, q), toVec(p, r))) < EPS


if __name__ == '__main__':
  P = [point(2e-9, 0), point(0, 2), point(1e-9, 1)]
  P = sorted(P)
  for pt in P:
    print('%.9lf, %.9lf' % (pt.x, pt.y))

  P1 = point()
  P2 = point()
  P3 = point(0, 1)
  print('%d' % (P1 == P2))
  print('%d' % (P1 == P3))

  P = [point(2, 2), point(4, 3), point(2, 4), point(6, 6), point(2, 6), point(6, 5)]

  P = sorted(P)
  for p in P:
    print('(%.2lf, %.2lf)' % (p.x, p.y))

  P = [point(2, 2), point(4, 3), point(2, 4), point(6, 6), point(2, 6), point(6, 5), point(8, 6)]

  d = dist(P[0], P[5])
  print('Euclidean distance between P[0] and P[5] = %.2lf' % d)

  l1 = line()
  l2 = line()
  l3 = line()
  l4 = line()

  pointsToLine(P[0], P[1], l1)
  print('%.2lf * x + %.2lf * y + %.2lf = 0.00' % (l1.a, l1.b, l1.c))

  pointsToLine(P[0], P[2], l2);
  print('%.2lf * x + %.2lf * y + %.2lf = 0.00' % (l2.a, l2.b, l2.c))


  pointsToLine(P[2], P[3], l3)
  print('l1 & l2 are parallel? %d' % areParallel(l1, l2))
  print('l1 & l3 are parallel? %d' % areParallel(l1, l3))

  pointsToLine(P[2], P[4], l4)
  print('l1 & l2 are the same? %d' % areSame(l1, l2))
  print('l2 & l4 are the same? %d' % areSame(l2, l4))
  
  p12 = point()
  res = areIntersect(l1, l2, p12)
  print('l1 & l2 are intersect? %d, at (%.2lf, %.2lf)' % (res, p12.x, p12.y))

  ans = point()
  d = distToLine(P[0], P[2], P[3], ans)
  print('Closest point from P[0] to line         (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf' % (ans.x, ans.y, d))
  closestPoint(l3, P[0], ans)
  print('Closest point from P[0] to line V2      (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf' % (ans.x, ans.y, dist(P[0], ans)))

  d = distToLineSegment(P[0], P[2], P[3], ans)
  print('Closest point from P[0] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf' % (ans.x, ans.y, d))
  d = distToLineSegment(P[1], P[2], P[3], ans)
  print('Closest point from P[1] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf' % (ans.x, ans.y, d))
  d = distToLineSegment(P[6], P[2], P[3], ans)
  print('Closest point from P[6] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf' % (ans.x, ans.y, d))

  reflectionPoint(l4, P[1], ans)
  print('Reflection point from P[1] to line      (P[2]-P[4]): (%.2lf, %.2lf)' % (ans.x, ans.y))

  print('Angle P[0]-P[4]-P[3] = %.2lf' % RAD_to_DEG(angle(P[0], P[4], P[3])))
  print('Angle P[0]-P[2]-P[1] = %.2lf' % RAD_to_DEG(angle(P[0], P[2], P[1])))
  print('Angle P[4]-P[3]-P[6] = %.2lf' % RAD_to_DEG(angle(P[4], P[3], P[6])))

  print('P[0], P[2], P[3] form A left turn? %d' % ccw(P[0], P[2], P[3]))
  print('P[0], P[3], P[2] form A left turn? %d' % ccw(P[0], P[3], P[2]))

  print('P[0], P[2], P[3] are collinear? %d' % collinear(P[0], P[2], P[3]))
  print('P[0], P[2], P[4] are collinear? %d' % collinear(P[0], P[2], P[4]))

  p = point(3, 7)
  q = point(11, 13)
  r = point(35, 30)
  print('r is on the %s of line p-q (direction p->q)' % ('left' if ccw(p, q, r) else 'right'))

  A = point(2.0, 2.0)
  B = point(4.0, 3.0)
  v = toVec(A, B)
  C = point(3.0, 2.0)
  D = translate(C, v)
  print('D = (%.2lf, %.2lf)' % (D.x, D.y))
  E = translate(C, scale(v, 0.5))
  print('E = (%.2lf, %.2lf)' % (E.x, E.y))

  print('B = (%.2lf, %.2lf)' % (B.x, B.y))
  F = rotate(B, 90)
  print('F = (%.2lf, %.2lf)' % (F.x, F.y))
  G = rotate(B, 180)
  print('G = (%.2lf, %.2lf)' % (G.x, G.y))
