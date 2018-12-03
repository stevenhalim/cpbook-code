import java.util.*;

class ch7_03_triangles {
  final double EPS = 1e-9;

  double DEG_to_RAD(double d) { return d * Math.PI / 180.0; }
  double RAD_to_DEG(double r) { return r * 180.0 / Math.PI; }

  class point_i {
    int x, y;                  // whenever possible, work with point_i
    point_i() { x = y = 0; }                    // default constructor
    point_i(int _x, int _y) { x = _x; y = _y; }         // constructor
  };

  class point {
    double x, y;              // only used if more precision is needed
    point() { x = y = 0.0; }                    // default constructor
    point(double _x, double _y) { x = _x; y = _y; }     // constructor
  };

  double dist(point p1, point p2) {
    return Math.hypot(p1.x - p2.x, p1.y - p2.y); }

  double perimeter(double ab, double bc, double ca) {
    return ab + bc + ca; }

  double perimeter(point a, point b, point c) {
    return dist(a, b) + dist(b, c) + dist(c, a); }

  double area(double ab, double bc, double ca) {
    // Heron's formula, split sqrt(a * b) into sqrt(a) * sqrt(b); in implementation
    double s = 0.5 * perimeter(ab, bc, ca);
    return Math.sqrt(s) * Math.sqrt(s - ab) * Math.sqrt(s - bc) * Math.sqrt(s - ca); }

  double area(point a, point b, point c) {
    return area(dist(a, b), dist(b, c), dist(c, a)); }

  //====================================================================
  // from ch7_01_points_lines
  class line { double a, b, c; };              // a way to represent a line

  // the answer is stored in the third parameter
  void pointsToLine(point p1, point p2, line l) {
    if (Math.abs(p1.x - p2.x) < EPS) {             // vertical line is fine
      l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;
    } else {
      l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
      l.b = 1.0;                 // IMPORTANT: we fix the value of b to 1.0
      l.c = -(double)(l.a * p1.x) - p1.y;
  } }

  boolean areParallel(line l1, line l2) {       // check coefficients a & b
    return (Math.abs(l1.a-l2.a) < EPS) && (Math.abs(l1.b-l2.b) < EPS); }

  // returns true (+ intersection point) if two lines are intersect
  boolean areIntersect(line l1, line l2, point p) {
    if (areParallel(l1, l2)) return false;               // no intersection
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // special case: test for vertical line to avoid division by zero
    if (Math.abs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else                      p.y = -(l2.a * p.x + l2.c);
    return true; }

  class vec { double x, y;     // name: `vec' is different from Java Vector
    vec(double _x, double _y) { x = _x; y = _y; } };

  vec toVec(point a, point b) {               // convert 2 points to vector
    return new vec(b.x - a.x, b.y - a.y); }

  vec scale(vec v, double s) {           // nonnegative s = [<1 .. 1 .. >1]
    return new vec(v.x * s, v.y * s); }              // shorter.same.longer

  point translate(point p, vec v) {           // translate p according to v
    return new point(p.x + v.x , p.y + v.y); }
  //====================================================================

  double rInCircle(double ab, double bc, double ca) {
    return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca)); }

  double rInCircle(point a, point b, point c) {
    return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }

  // assumption: the required points/lines functions have been written
  // returns 1 if there is an inCircle center, returns 0 otherwise
  // if this function returns 1, ctr will be the inCircle center
  // and r is the same as rInCircle
  int inCircle(point p1, point p2, point p3, point ctr, double r) {
    r = rInCircle(p1, p2, p3);
    if (Math.abs(r) < EPS) return 0;               // no inCircle center

    line l1 = new line(), l2 = new line(); // compute these two angle bisectors
    double ratio = dist(p1, p2) / dist(p1, p3);
    point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
    pointsToLine(p1, p, l1);

    ratio = dist(p2, p1) / dist(p2, p3);
    p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
    pointsToLine(p2, p, l2);

    areIntersect(l1, l2, ctr);           // get their intersection point
    return 1; }

  double rCircumCircle(double ab, double bc, double ca) {
    return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

  double rCircumCircle(point a, point b, point c) {
    return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }

  // assumption: the required points/lines functions have been written
  // returns r, the radius of the circumCircle if there is a circumCenter center,
  // and set ctr to be the circumCircle center
  // returns 0 otherwise
  double circumCircle(point p1, point p2, point p3, point ctr) {
    double a = p2.x - p1.x, b = p2.y - p1.y;
    double c = p3.x - p1.x, d = p3.y - p1.y;
    double e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
    double f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
    double g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
    if (Math.abs(g) < EPS) return 0;

    ctr.x = (d*e - b*f) / g;
    ctr.y = (a*f - c*e) / g;
    return dist(p1, ctr); } // distance from center to 1 of the 3 points

  // returns true if point d is inside the circumCircle defined by a,b,c
  boolean inCircumCircle(point a, point b, point c, point d) {
    return ((a.x - d.x) * (b.y - d.y) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) +
            (a.y - d.y) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.x - d.x) +
            ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.x - d.x) * (c.y - d.y) -
            ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.y - d.y) * (c.x - d.x) -
            (a.y - d.y) * (b.x - d.x) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) -
            (a.x - d.x) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.y - d.y)) > 0.0;
  }

  boolean canFormTriangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a); }

  void run() {
    double base = 4.0, h = 3.0;
    double A = 0.5 * base * h;
    System.out.printf("Area = %.2f\n", A);

    point a = new point();                         // a right triangle
    point b = new point(4.0, 0.0);
    point c = new point(4.0, 3.0);

    double p = perimeter(a, b, c);
    double s = 0.5 * p;
    A = area(a, b, c);
    System.out.printf("Area = %.2f\n", A); // must be the same as above

    double r = rInCircle(a, b, c);
    System.out.printf("R1 (radius of incircle) = %.2f\n", r); // 1.00
    point ctr = new point();
    int res = inCircle(a, b, c, ctr, r);
    System.out.printf("R1 (radius of incircle) = %.2f\n", r); // same, 1.00
    System.out.printf("Center = (%.2f, %.2f)\n", ctr.x, ctr.y); // (3.00, 1.00)

    System.out.printf("R2 (radius of circumcircle) = %.2f\n", rCircumCircle(a, b, c)); // 2.50
    r = circumCircle(a, b, c, ctr);
    System.out.printf("R2 (radius of circumcircle) = %.2f\n", r); // same, 2.50
    System.out.printf("Center = (%.2f, %.2f)\n", ctr.x, ctr.y); // (2.00, 1.50)

    point d = new point(2.0, 1.0); // inside triangle and circumCircle
    System.out.printf("d inside circumCircle (a, b, c) ? %b\n", inCircumCircle(a, b, c, d));
    point e = new point(2.0, 3.9); // outside the triangle but inside circumCircle
    System.out.printf("e inside circumCircle (a, b, c) ? %b\n", inCircumCircle(a, b, c, e));
    point f = new point(2.0, -1.1); // slightly outside
    System.out.printf("f inside circumCircle (a, b, c) ? %b\n", inCircumCircle(a, b, c, f));

    // Law of Cosines
    double ab = dist(a, b);
    double bc = dist(b, c);
    double ca = dist(c, a);
    double alpha = RAD_to_DEG(Math.acos((ca * ca + ab * ab - bc * bc) / (2.0 * ca * ab)));
    System.out.printf("alpha = %.2f\n", alpha);
    double beta  = RAD_to_DEG(Math.acos((ab * ab + bc * bc - ca * ca) / (2.0 * ab * bc)));
    System.out.printf("beta  = %.2f\n", beta);
    double gamma = RAD_to_DEG(Math.acos((bc * bc + ca * ca - ab * ab) / (2.0 * bc * ca)));
    System.out.printf("gamma = %.2f\n", gamma);

    // Law of Sines
    System.out.printf("%.2f == %.2f == %.2f\n", 
      bc / Math.sin(DEG_to_RAD(alpha)),
      ca / Math.sin(DEG_to_RAD(beta)),
      ab / Math.sin(DEG_to_RAD(gamma)));

    // Phytagorean Theorem
    System.out.printf("%.2f^2 == %.2f^2 + %.2f^2\n", ca, ab, bc);

    // Triangle Inequality
    System.out.printf("(%d, %d, %d) => can form triangle? %b\n", 3, 4, 5, canFormTriangle(3, 4, 5)); // yes
    System.out.printf("(%d, %d, %d) => can form triangle? %b\n", 3, 4, 7, canFormTriangle(3, 4, 7)); // no, actually straight line
    System.out.printf("(%d, %d, %d) => can form triangle? %b\n", 3, 4, 8, canFormTriangle(3, 4, 8)); // no
  }

  public static void main(String[] args){
    new ch7_03_triangles().run();
  }
}
