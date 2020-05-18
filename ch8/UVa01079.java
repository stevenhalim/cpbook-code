// World Finals Stockholm 2009, A - A Careful Approach, UVa 1079, LA 4445, 0.???s in Java, 0.578s in C++

import java.util.*;

class UVa01079 {
  static double[] a = new double[8], b = new double[8];
  static int[] order = new int[8], arr = new int[8];
  static int i, n, caseNo = 1;
  static double L, maxL;

  static double greedyLanding() {  // with certain landing order, and certain L, try
           // landing those planes and see what is the gap to b[order[n - 1]]
    double lastLanding = a[order[0]];      // greedy, 1st aircraft lands ASAP
    for (i = 1; i < n; i++) {                      // for the other aircrafts
      double targetLandingTime = lastLanding + L;
      if (targetLandingTime <= b[order[i]])
         // can land: greedily choose max of a[order[i]] or targetLandingTime
        lastLanding = Math.max(a[order[i]], targetLandingTime);
      else
        return 1;
    }
    // return +ve value to force binary search to reduce L
    // return -ve value to force binary search to increase L
    return lastLanding - b[order[n - 1]];
  }

  static int LSOne(int v) { return v & (-v); }

  static void permutate(int cur, int unused) { // Java does not have next_permutation like C++ <algorithm>
    if (cur == n) {
      // do things to curPermute
      double lo = 0, hi = 86400;              // min 0s, max 1 day = 86400s
      L = -1;                          // start with an infeasible solution
      while (Math.abs(lo - hi) >= 1e-3) {    // binary search L, EPS = 1e-3
        L = (lo + hi) / 2.0;   // we want the answer rounded to nearest int
        double retVal = greedyLanding();                // round down first
        if (retVal <= 1e-2) lo = L;                      // must increase L
        else                hi = L;          // infeasible, must decrease L
      }
      maxL = Math.max(maxL, L);        // get the max over all permutations
      return;
    }

    int p = unused;
    while (p > 0) {
      int c = LSOne(p);
      p -= c;
      int i = (int)(Math.log(c) / Math.log(2));
      order[cur] = arr[i];
      permutate(cur + 1, unused - c);
    }
  }

  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    while (true) {
      n = sc.nextInt();                                        // 2 <= n <= 8
      if (n == 0) break;

      for (i = 0; i < n; i++) {   // plane i land safely at interval [ai, bi]
        a[i] = sc.nextDouble(); b[i] = sc.nextDouble();
        a[i] *= 60; b[i] *= 60;  // originally in minutes, convert to seconds
        order[i] = i;
        arr[i] = i;
      }

      maxL = -1.0;                             // variable to be searched for
      permutate(0, (1 << n) - 1);    // permute plane landing order, up to 8!

      int secs = (int)Math.round(maxL);            // round to nearest second
      System.out.printf("Case %d: %d:%02d\n", caseNo++, secs/60, secs%60);
    }
  }
}
