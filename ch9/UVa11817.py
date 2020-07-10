from math import cos, acos, sin, asin, pi, sqrt

EARTH_RAD = 6371009

def gcDistance(pLat, pLong, qLat, qLong, radius):
  pLat  *= pi / 180
  pLong *= pi / 180
  qLat  *= pi / 180
  qLong *= pi / 180
  return radius * acos(cos(pLat)*cos(pLong)*cos(qLat)*cos(qLong) +\
                       cos(pLat)*sin(pLong)*cos(qLat)*sin(qLong) +\
                       sin(pLat)*sin(qLat))


def EuclideanDistance(pLat, pLong, qLat, qLong, radius):
  phi1 = (90 - pLat) * pi / 180
  theta1 = (360 - pLong) * pi / 180
  x1 = radius * sin(phi1) * cos(theta1)
  y1 = radius * sin(phi1) * sin(theta1)
  z1 = radius * cos(phi1)

  phi2 = (90 - qLat) * pi / 180
  theta2 = (360 - qLong) * pi / 180
  x2 = radius * sin(phi2) * cos(theta2)
  y2 = radius * sin(phi2) * sin(theta2)
  z2 = radius * cos(phi2)

  dx = x1 - x2
  dy = y1 - y2
  dz = z1 - z2
  return sqrt(dx * dx + dy * dy + dz * dz)


def main():
  TC = int(input())
  for _ in range(TC):
    lat1, lon1, lat2, lon2 = map(float, input().split())
    print('%.lf' % (gcDistance(lat1, lon1, lat2, lon2, EARTH_RAD) -\
                    EuclideanDistance(lat1, lon1, lat2, lon2, EARTH_RAD)))


main()
