import java.util.*;

class ch7_01_points_lines {
  final double INF = 1e9;
  final double EPS = 1e-9;
  // we will use constant Math.PI in Java

  double DEG_to_RAD(double d) { return d * Math.PI / 180.0; }

  double RAD_to_DEG(double r) { return r * 180.0 / Math.PI; }

  //struct point_i { int x, y; };        // basic raw form, minimalist mode
  class point_i { int x, y;         // whenever possible, work with point_i
    point_i() { x = y = 0; }                         // default constructor
    point_i(int _x, int _y) { x = _x; y = _y; } };          // user-defined
  
  class point implements Comparable<point>{
    double x, y;                   // only used if more precision is needed
    point() { x = y = 0.0; }                         // default constructor
    point(double _x, double _y) { x = _x; y = _y; }         // user-defined
    // use EPS (1e-9) when testing equality of two floating points
    public int compareTo(point other) {      // override less than operator
      if (Math.abs(x - other.x) > EPS)                // useful for sorting
        return (int)Math.ceil(x - other.x);       // first: by x-coordinate
      else if (Math.abs(y - other.y) > EPS)
        return (int)Math.ceil(y - other.y);      // second: by y-coordinate
      else
        return 0; } };                                    // they are equal

  double dist(point p1, point p2) {                   // Euclidean distance
                      // Math.hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return Math.hypot(p1.x - p2.x, p1.y - p2.y); }         // return double

  // rotate p by theta degrees CCW w.r.t origin (0, 0)
  point rotate(point p, double theta) {
    double rad = DEG_to_RAD(theta);       // multiply theta with PI / 180.0
    return new point(p.x * Math.cos(rad) - p.y * Math.sin(rad),
                     p.x * Math.sin(rad) + p.y * Math.cos(rad)); }

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

  // not needed since we will use the more robust form: ax + by + c = 0 (see above)
  class line2 { double m, c; };          // another way to represent a line
  
  int pointsToLine2(point p1, point p2, line2 l) {
   if (Math.abs(p1.x - p2.x) < EPS) {        // special case: vertical line
     l.m = INF;                       // l contains m = INF and c = x_value
     l.c = p1.x;                     // to denote vertical line x = x_value
     return 0;      // we need this return variable to differentiate result
   }
   else {
     l.m = (double)(p1.y - p2.y) / (p1.x - p2.x);
     l.c = p1.y - l.m * p1.x;
     return 1;        // l contains m and c of the line equation y = mx + c
  } }

  boolean areParallel(line l1, line l2) {       // check coefficients a & b
    return (Math.abs(l1.a-l2.a) < EPS) && (Math.abs(l1.b-l2.b) < EPS); }

  boolean areSame(line l1, line l2) {           // also check coefficient c
    return areParallel(l1 ,l2) && (Math.abs(l1.c - l2.c) < EPS); }

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

  // convert point and gradient/slope to line
  void pointSlopeToLine(point p, double m, line l) {
    l.a = -m;                                                  // always -m
    l.b = 1;                                                    // always 1
    l.c = -((l.a * p.x) + (l.b * p.y)); }                   // compute this

  void closestPoint(line l, point p, point ans) {
    line perpendicular = new line(); // perpendicular to l and pass through p
    if (Math.abs(l.b) < EPS) {             // special case 1: vertical line
      ans.x = -(l.c);   ans.y = p.y;      return; }

    if (Math.abs(l.a) < EPS) {           // special case 2: horizontal line
      ans.x = p.x;      ans.y = -(l.c);   return; }

    pointSlopeToLine(p, 1 / l.a, perpendicular);             // normal line
    // intersect line l with this perpendicular line
    // the intersection point is the closest point
    areIntersect(l, perpendicular, ans); }

  // returns the reflection of point on a line
  void reflectionPoint(line l, point p, point ans) {
    point b = new point();
    closestPoint(l, p, b);                         // similar to distToLine
    vec v = toVec(p, b);                                 // create a vector
    ans = translate(translate(p, v), v); }             // translate p twice

  double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

  double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

  // returns the distance from p to the line defined by
  // two points a and b (a and b must be different)
  // the closest point is stored in the 4th parameter
  double distToLine(point p, point a, point b, point c) {
    // formula: c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));                     // translate a to c
    return dist(p, c); }              // Euclidean distance between p and c

  // returns the distance from p to the line segment ab defined by
  // two points a and b (still OK if a == b)
  // the closest point is stored in the 4th parameter
  double distToLineSegment(point p, point a, point b, point c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) { c = new point(a.x, a.y);                  // closer to a
      return dist(p, a); }            // Euclidean distance between p and a
    if (u > 1.0) { c = new point(b.x, b.y);                  // closer to b
      return dist(p, b); }            // Euclidean distance between p and b
    return distToLine(p, a, b, c); }             // run distToLine as above

  double angle(point a, point o, point b) {     // returns angle aob in rad
    vec oa = toVec(o, a), ob = toVec(o, b);
    return Math.acos(dot(oa, ob) / Math.sqrt(norm_sq(oa) * norm_sq(ob))); }

  double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

  //// another variant
  //int area2(point p, point q, point r) { // returns 'twice' the area of this triangle A-B-c
  //  return p.x * q.y - p.y * q.x +
  //         q.x * r.y - q.y * r.x +
  //         r.x * p.y - r.y * p.x;
  //}

  // note: to accept collinear points, we have to change the `> 0'
  // returns true if point r is on the left side of line pq
  boolean ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0; }

  // returns true if point r is on the same line as the line pq
  boolean collinear(point p, point q, point r) {
    return Math.abs(cross(toVec(p, q), toVec(p, r))) < EPS; }

  void run() {
    point P1 = new point(), P2 = new point(), P3 = new point(0, 1); // note that both P1 and P2 are (0.00, 0.00)
    System.out.println(P1.compareTo(P2) == 0);                      // true
    System.out.println(P1.compareTo(P3) == 0);                     // false

    point[] P = new point[6];
    P[0] = new point(2, 2);
    P[1] = new point(4, 3);
    P[2] = new point(2, 4);
    P[3] = new point(6, 6);
    P[4] = new point(2, 6);
    P[5] = new point(6, 5);

    // sorting points demo
    Arrays.sort(P);
    for (int i = 0; i < P.length; i++)
      System.out.printf("(%.2f, %.2f)\n", P[i].x, P[i].y);

    // rearrange the points as shown in the diagram below
    P = new point[7];
    P[0] = new point(2, 2);
    P[1] = new point(4, 3);
    P[2] = new point(2, 4);
    P[3] = new point(6, 6);
    P[4] = new point(2, 6);
    P[5] = new point(6, 5);
    P[6] = new point(8, 6);
  
    /*
    // the positions of these 7 points (0-based indexing)
    6   P4      P3  P6
    5           P5
    4   P2
    3       P1
    2   P0
    1
    0 1 2 3 4 5 6 7 8
    */

    double d = dist(P[0], P[5]);
    System.out.printf("Euclidean distance between P[0] and P[5] = %.2f\n", d); // should be 5.000

    // line equations
    line l1 = new line(), l2 = new line(), l3 = new line(), l4 = new line();

    pointsToLine(P[0], P[1], l1);
    System.out.printf("%.2f * x + %.2f * y + %.2f = 0.00\n", l1.a, l1.b, l1.c); // should be -0.50 * x + 1.00 * y - 1.00 = 0.00

    pointsToLine(P[0], P[2], l2); // a vertical line, not a problem in "ax + by + c = 0" representation
    System.out.printf("%.2f * x + %.2f * y + %.2f = 0.00\n", l2.a, l2.b, l2.c); // should be 1.00 * x + 0.00 * y - 2.00 = 0.00

    // parallel, same, and line intersection tests
    pointsToLine(P[2], P[3], l3);
    System.out.printf("l1 & l2 are parallel? %b\n", areParallel(l1, l2)); // no
    System.out.printf("l1 & l3 are parallel? %b\n", areParallel(l1, l3)); // yes, l1 (P[0]-P[1]) and l3 (P[2]-P[3]) are parallel

    pointsToLine(P[2], P[4], l4);
    System.out.printf("l1 & l2 are the same? %b\n", areSame(l1, l2)); // no
    System.out.printf("l2 & l4 are the same? %b\n", areSame(l2, l4)); // yes, l2 (P[0]-P[2]) and l4 (P[2]-P[4]) are the same line (note, they are two different line segments, but same line)

    point p12 = new point();
    boolean res = areIntersect(l1, l2, p12); // yes, l1 (P[0]-P[1]) and l2 (P[0]-P[2]) are intersect at (2.0, 2.0)
    System.out.printf("l1 & l2 are intersect? %b, at (%.2f, %.2f)\n", res, p12.x, p12.y);

    // other distances
    point ans = new point();
    d = distToLine(P[0], P[2], P[3], ans);
    System.out.printf("Closest point from P[0] to line         (P[2]-P[3]): (%.2f, %.2f), dist = %.2f\n", ans.x, ans.y, d);
    closestPoint(l3, P[0], ans);
    System.out.printf("Closest point from P[0] to line V2      (P[2]-P[3]): (%.2f, %.2f), dist = %.2f\n", ans.x, ans.y, dist(P[0], ans));

    d = distToLineSegment(P[0], P[2], P[3], ans);
    System.out.printf("Closest point from P[0] to line SEGMENT (P[2]-P[3]): (%.2f, %.2f), dist = %.2f\n", ans.x, ans.y, d); // closer to A (or P[2]) = (2.00, 4.00)
    d = distToLineSegment(P[1], P[2], P[3], ans);
    System.out.printf("Closest point from P[1] to line SEGMENT (P[2]-P[3]): (%.2f, %.2f), dist = %.2f\n", ans.x, ans.y, d); // closer to midway between AB = (3.20, 4.60)
    d = distToLineSegment(P[6], P[2], P[3], ans);
    System.out.printf("Closest point from P[6] to line SEGMENT (P[2]-P[3]): (%.2f, %.2f), dist = %.2f\n", ans.x, ans.y, d); // closer to B (or P[3]) = (6.00, 6.00)

    reflectionPoint(l4, P[1], ans);
    System.out.printf("Reflection point from P[1] to line      (P[2]-P[4]): (%.2f, %.2f)\n", ans.x, ans.y); // should be (0.00, 3.00)

    System.out.printf("Angle P[0]-P[4]-P[3] = %.2f\n", RAD_to_DEG(angle(P[0], P[4], P[3]))); // 90 degrees
    System.out.printf("Angle P[0]-P[2]-P[1] = %.2f\n", RAD_to_DEG(angle(P[0], P[2], P[1]))); // 63.43 degrees
    System.out.printf("Angle P[4]-P[3]-P[6] = %.2f\n", RAD_to_DEG(angle(P[4], P[3], P[6]))); // 180 degrees

    System.out.printf("P[0], P[2], P[3] form A left turn? %b\n", ccw(P[0], P[2], P[3])); // no
    System.out.printf("P[0], P[3], P[2] form A left turn? %b\n", ccw(P[0], P[3], P[2])); // yes

    System.out.printf("P[0], P[2], P[3] are collinear? %b\n", collinear(P[0], P[2], P[3])); // no
    System.out.printf("P[0], P[2], P[4] are collinear? %b\n", collinear(P[0], P[2], P[4])); // yes

    point p = new point(3, 7), q = new point(11, 13), r = new point(35, 30); // collinear if r(35, 31)
    System.out.printf("r is on the %s of line p-r\n", ccw(p, q, r) ? "left" : "right"); // right
  
    /*
    // the positions of these 6 points
       E<--  4
             3       B D<--
             2   A C
             1
    -4-3-2-1 0 1 2 3 4 5 6
            -1
            -2
     F<--   -3
    */

    // translation
    point A = new point(2.0, 2.0);
    point B = new point(4.0, 3.0);
    vec v = toVec(A, B); // imagine there is an arrow from A to B (see the diagram above)
    point C = new point(3.0, 2.0);
    point D = translate(C, v); // D will be located in coordinate (3.0 + 2.0, 2.0 + 1.0) = (5.0, 3.0)
    System.out.printf("D = (%.2f, %.2f)\n", D.x, D.y);
    point E = translate(C, scale(v, 0.5)); // E will be located in coordinate (3.0 + 1/2 * 2.0, 2.0 + 1/2 * 1.0) = (4.0, 2.5)
    System.out.printf("E = (%.2f, %.2f)\n", E.x, E.y);

    // rotation
    System.out.printf("B = (%.2f, %.2f)\n", B.x, B.y); // B = (4.0, 3.0)
    point F = rotate(B, 90); // rotate B by 90 degrees COUNTER clockwise, F = (-3.0, 4.0)
    System.out.printf("F = (%.2f, %.2f)\n", F.x, F.y);
    point G = rotate(B, 180); // rotate B by 180 degrees COUNTER clockwise, G = (-4.0, -3.0)
    System.out.printf("G = (%.2f, %.2f)\n", G.x, G.y);
  }

  public static void main(String[] args){
    new ch7_01_points_lines().run();
  }
}
