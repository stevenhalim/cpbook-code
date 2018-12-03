// Tunnelling the Earth

#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1.0)
#define EARTH_RAD (6371009) // in meters

double gcDistance(double pLat, double pLong,
                  double qLat, double qLong, double radius) {
  pLat *= PI / 180; pLong *= PI / 180;
  qLat *= PI / 180; qLong *= PI / 180;
  return radius * acos(cos(pLat)*cos(pLong)*cos(qLat)*cos(qLong) +
                       cos(pLat)*sin(pLong)*cos(qLat)*sin(qLong) +
                       sin(pLat)*sin(qLat));
}

double EucledianDistance(double pLat, double pLong, // 3D version
                         double qLat, double qLong, double radius) {
  double phi1 = (90 - pLat) * PI / 180;
  double theta1 = (360 - pLong) * PI / 180;
  double x1 = radius * sin(phi1) * cos(theta1);
  double y1 = radius * sin(phi1) * sin(theta1);
  double z1 = radius * cos(phi1);

  double phi2 = (90 - qLat) * PI / 180;
  double theta2 = (360 - qLong) * PI / 180;
  double x2 = radius * sin(phi2) * cos(theta2);
  double y2 = radius * sin(phi2) * sin(theta2);
  double z2 = radius * cos(phi2);

  double dx = x1 - x2, dy = y1 - y2, dz = z1 - z2;
  return sqrt(dx * dx + dy * dy + dz * dz);
}

int main() {
  int TC;
  double lat1, lon1, lat2, lon2;

  scanf("%d", &TC);
  while (TC--) {
    scanf("%lf %lf %lf %lf", &lat1, &lon1, &lat2, &lon2);
    printf("%.0lf\n", gcDistance(lat1, lon1, lat2, lon2, EARTH_RAD) -
                      EucledianDistance(lat1, lon1, lat2, lon2, EARTH_RAD));
  }

  return 0;
}
