class circles {
  double DEG_to_RAD(double d) { return d*Math.PI/180.0; }
  double RAD_to_DEG(double r) { return r*180.0/Math.PI; }

  class point_i {
    int x, y;                                    // use this if possible
    point_i() { x = y = 0; }                     // default constructor
    point_i(int _x, int _y) { x = _x; y = _y; }  // constructor
  };

  class point {
    double x, y;                                 // if need more precision
    point() { x = y = 0.0; }                     // default constructor
    point(double _x, double _y) { x = _x; y = _y; } // constructor
  };

  int insideCircle(point_i p, point_i c, int r) { // all integer version
    int dx = p.x-c.x, dy = p.y-c.y;
    int Euc = dx*dx + dy*dy, rSq = r*r;          // all integer
    return Euc < rSq ? 1 : Euc == rSq ? 0 : -1;  // inside/border/outside
  }

  boolean circle2PtsRad(point p1, point p2, double r, point c) {
    double d2 = (p1.x-p2.x) * (p1.x-p2.x) + 
                (p1.y-p2.y) * (p1.y-p2.y);
    double det = r*r / d2 - 0.25;
    if (det < 0.0) return false;
    double h = Math.sqrt(det);
    c.x = (p1.x+p2.x) * 0.5 + (p1.y-p2.y) * h;
    c.y = (p1.y+p2.y) * 0.5 + (p2.x-p1.x) * h;
    return true;
  }

  void run() {
    // circle equation, inside, border, outside
    point_i pt = new point_i(2, 2);
    int r = 7;
    point_i inside = new point_i(8, 2);
    System.out.printf("%d\n", insideCircle(inside, pt, r)); // 1, inside
    point_i border = new point_i(9, 2);
    System.out.printf("%d\n", insideCircle(border, pt, r)); // 0, at border
    point_i outside = new point_i(10, 2);
    System.out.printf("%d\n", insideCircle(outside, pt, r)); // -1, outside

    double d = 2 * r;
    System.out.printf("Diameter = %.2f\n", d);
    double c = Math.PI * d;
    System.out.printf("Circumference / Perimeter = %.2f\n", c);
    double A = Math.PI * r * r;
    System.out.printf("Area of circle = %.2f\n", A);

    System.out.printf("Length of arc (central angle = 60 degrees) = %.2f\n", 60.0/360.0*c);
    System.out.printf("Length of chord (central angle = 60 degrees) = %.2f\n",
      Math.sqrt((2*r*r) * (1 - Math.cos(DEG_to_RAD(60.0)))));
    System.out.printf("Area of sector (central angle = 60 degrees) = %.2f\n", 60.0/360.0*A);

    point p1 = new point();
    point p2 = new point(0.0, -1.0);
    point ans = new point();
    circle2PtsRad(p1, p2, 2.0, ans);
    System.out.printf("One of the center is (%.2f, %.2f)\n", ans.x, ans.y);
    circle2PtsRad(p2, p1, 2.0, ans);
    System.out.printf("The other center  is (%.2f, %.2f)\n", ans.x, ans.y);
  }

  public static void main(String[] args){
    new circles().run();
  }
}
