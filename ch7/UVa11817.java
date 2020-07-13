// Tunnelling the Earth
// Great Circle distance + Euclidean distance
// 0.852s in Java, 0.019s in C++

import java.util.*;

class Main {
  static final int EARTH_RAD = 6371009; // in meters

  static double gcDistance(double pLat, double pLong,
                    double qLat, double qLong, double radius) {
    pLat *= Math.PI / 180; pLong *= Math.PI / 180;
    qLat *= Math.PI / 180; qLong *= Math.PI / 180;
    return radius * Math.acos(Math.cos(pLat)*Math.cos(pLong)*Math.cos(qLat)*Math.cos(qLong) +
                         Math.cos(pLat)*Math.sin(pLong)*Math.cos(qLat)*Math.sin(qLong) +
                         Math.sin(pLat)*Math.sin(qLat));
  }

  static double EucledianDistance(double pLat, double pLong, // 3D version
                           double qLat, double qLong, double radius) {
    double phi1 = (90 - pLat) * Math.PI / 180;
    double theta1 = (360 - pLong) * Math.PI / 180;
    double x1 = radius * Math.sin(phi1) * Math.cos(theta1);
    double y1 = radius * Math.sin(phi1) * Math.sin(theta1);
    double z1 = radius * Math.cos(phi1);

    double phi2 = (90 - qLat) * Math.PI / 180;
    double theta2 = (360 - qLong) * Math.PI / 180;
    double x2 = radius * Math.sin(phi2) * Math.cos(theta2);
    double y2 = radius * Math.sin(phi2) * Math.sin(theta2);
    double z2 = radius * Math.cos(phi2);

    double dx = x1 - x2, dy = y1 - y2, dz = z1 - z2;
    return Math.sqrt(dx * dx + dy * dy + dz * dz);
  }

  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    int TC = scan.nextInt();
    while (TC-- > 0) {
      double lat1 = scan.nextDouble();
      double lon1 = scan.nextDouble();
      double lat2 = scan.nextDouble();
      double lon2 = scan.nextDouble();
      System.out.printf("%.0f\n", gcDistance(lat1, lon1, lat2, lon2, EARTH_RAD) -
                                  EucledianDistance(lat1, lon1, lat2, lon2, EARTH_RAD));
    }
  }
}
