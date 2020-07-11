// Tunnelling the Earth

#include <bits/stdc++.h>
using namespace std;

#define EARTH_RAD (6371009) // in meters

double gcDist(double pLa, double pLo, double qLa, double qLo, double r) {
  pLa *= M_PI/180; pLo *= M_PI/180;           // degree to radian
  qLa *= M_PI/180; qLo *= M_PI/180;
  return r * acos(cos(pLa)*cos(pLo)*cos(qLa)*cos(qLo) +
         cos(pLa)*sin(pLo)*cos(qLa)*sin(qLo) + sin(pLa)*sin(qLa));
}

// double gcDistance(double pLa, double pLo,
//                   double qLa, double qLo, double radius) {
//   pLa *= M_PI/180; pLo *= M_PI/180;           // degree to radian
//   qLa *= M_PI/180; qLo *= M_PI/180;
//   return radius * acos(cos(pLa)*cos(pLo)*cos(qLa)*cos(qLo) +
//                        cos(pLa)*sin(pLo)*cos(qLa)*sin(qLo) +
//                        sin(pLa)*sin(qLa));
// }

double EuclideanDistance(double pLa, double pLo, // 3D version
                         double qLa, double qLo, double radius) {
  double phi1 = (90 - pLa) * M_PI/180;
  double theta1 = (360 - pLo) * M_PI/180;
  double x1 = radius * sin(phi1) * cos(theta1);
  double y1 = radius * sin(phi1) * sin(theta1);
  double z1 = radius * cos(phi1);

  double phi2 = (90 - qLa) * M_PI/180;
  double theta2 = (360 - qLo) * M_PI/180;
  double x2 = radius * sin(phi2) * cos(theta2);
  double y2 = radius * sin(phi2) * sin(theta2);
  double z2 = radius * cos(phi2);

  double dx = x1 - x2, dy = y1 - y2, dz = z1 - z2;
  return sqrt(dx * dx + dy * dy + dz * dz);
}

int main() {
  int TC; scanf("%d", &TC);
  while (TC--) {
    double lat1, lon1, lat2, lon2; scanf("%lf %lf %lf %lf", &lat1, &lon1, &lat2, &lon2);
    printf("%.0lf\n", gcDist(lat1, lon1, lat2, lon2, EARTH_RAD) -
                      EuclideanDistance(lat1, lon1, lat2, lon2, EARTH_RAD));
  }
  return 0;
}
