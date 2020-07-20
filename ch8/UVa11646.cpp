// Athletics Track
// see the figure in Chapter 8.7
// the key = center of circle is at center of track

#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b, caseNo = 0;
  while (scanf("%d : %d", &a, &b) != EOF) {
    double lo = 0.0, hi = 400.0, L, W;           // the range of answer
    for (int i = 0; i < 40; ++i) {
      L = (lo+hi) / 2.0;                         // bisection method on L
      W = (double)b/a*L;                         // derive W from L and a:b
      double expected_arc = (400 - 2.0*L) / 2.0; // reference value
      double CM = 0.5*L, MX = 0.5*W;             // Apply Trigonometry here
      double r = sqrt(CM*CM + MX*MX);
      double angle = 2.0 * atan(MX/CM) * 180.0/M_PI;
      double this_arc = angle/360.0 * M_PI * (2.0*r);
      (this_arc > expected_arc) ? hi = L : lo = L;
    }
    printf("Case %d: %.12lf %.12lf\n", ++caseNo, L, W);
  }
  return 0;
}
