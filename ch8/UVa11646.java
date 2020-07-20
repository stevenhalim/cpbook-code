// Athletics Track
// see the figure in Chapter 8.7
// the key = center of circle is at center of track

import java.util.*;

class UVa11646 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int caseNo = 0;
    while (sc.hasNext()) {
      int a = sc.nextInt();
      String ch = sc.next();
      int b = sc.nextInt();
      double lo = 0.0, hi = 400.0, L = 0, W = 0;   // the range of answer
      for (int i = 0; i < 40; ++i) {
        L = (lo+hi) / 2.0;                         // bisection method on L
        W = (double)b/a*L;                         // derive W from L and a:b
        double expected_arc = (400 - 2.0*L) / 2.0; // reference value
        double CM = 0.5*L, MX = 0.5*W;             // Apply Trigonometry here
        double r = Math.sqrt(CM*CM + MX*MX);
        double angle = 2.0 * Math.atan(MX/CM) * 180.0/Math.PI;
        double this_arc = angle/360.0 * Math.PI * (2.0*r);
        if (this_arc > expected_arc)
          hi = L;
        else
          lo = L;
      }
      System.out.printf("Case %d: %.12f %.12f\n", ++caseNo, L, W);
    }
  }
}
