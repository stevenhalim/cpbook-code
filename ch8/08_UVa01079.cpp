// World Finals Stockholm 2009, A - A Careful Approach, UVa 1079, LA 4445

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int i, n, caseNo = 1, order[8];
double a[8], b[8], L, maxL;

double greedyLanding() {  // with certain landing order, and certain L, try
         // landing those planes and see what is the gap to b[order[n - 1]]
  double lastLanding = a[order[0]];      // greedy, 1st aircraft lands ASAP
  for (i = 1; i < n; i++) {                      // for the other aircrafts
    double targetLandingTime = lastLanding + L;
    if (targetLandingTime <= b[order[i]])
       // can land: greedily choose max of a[order[i]] or targetLandingTime
      lastLanding = max(a[order[i]], targetLandingTime);
    else
      return 1;
  }
  // return +ve value to force binary search to reduce L
  // return -ve value to force binary search to increase L
  return lastLanding - b[order[n - 1]];
}

int main() {
  while (scanf("%d", &n), n) {                               // 2 <= n <= 8
    for (i = 0; i < n; i++) {   // plane i land safely at interval [ai, bi]
      scanf("%lf %lf", &a[i], &b[i]);
      a[i] *= 60; b[i] *= 60;  // originally in minutes, convert to seconds
      order[i] = i;
    }

    maxL = -1.0;                             // variable to be searched for
    do {                           // permute plane landing order, up to 8!
      double lo = 0, hi = 86400;              // min 0s, max 1 day = 86400s
      L = -1;                          // start with an infeasible solution
      while (fabs(lo - hi) >= 1e-3) {        // binary search L, EPS = 1e-3
        L = (lo + hi) / 2.0;   // we want the answer rounded to nearest int
        double retVal = greedyLanding();                // round down first
        if (retVal <= 1e-2) lo = L;                      // must increase L
        else                hi = L;          // infeasible, must decrease L
      }
      maxL = max(maxL, L);             // get the max over all permutations
    }
    while (next_permutation(order, order + n));     // try all permutations

    // other way for rounding is to use printf format string: %.0lf:%0.2lf
    maxL = (int)(maxL + 0.5);                    // round to nearest second
    printf("Case %d: %d:%0.2d\n", caseNo++, (int)(maxL/60), (int)maxL%60);
  }

  return 0;
}
