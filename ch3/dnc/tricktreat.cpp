// Trick or Treat
// Ternary Search

#include <bits/stdc++.h>
using namespace std;

const int MAX_n = 50010;
const double INF = 1e9;

int n;
double xs[MAX_n], ys[MAX_n]; // big, just make it global

double f(double x) { // square of earliest meeting time if all n kids meet at coordinate (x, y = 0.0)
  double ans = -INF;
  for (int i = 0; i < n; ++i) // all n kids dash to (x, y = 0.0)
    ans = max(ans, (xs[i]-x) * (xs[i]-x) + ys[i] * ys[i]); // avoid computing sqrt which is slow
  return ans;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL);
  while (cin >> n, n) {
    double lo = INF, hi = -INF;
    for (int i = 0; i < n; ++i) {
      cin >> xs[i] >> ys[i];
      lo = min(lo, xs[i]);
      hi = max(hi, xs[i]);
    }
    for (int i = 0; i < 50; ++i) {                   // similar as BSTA
      double delta = (hi-lo)/3.0;                    // 1/3rd of the range
      double m1 = lo+delta;                          // 1/3rd away from lo
      double m2 = hi-delta;                          // 1/3rd away from hi
      (f(m1) > f(m2)) ? lo = m1 : hi = m2;           // f is unimodal
    }
    cout << fixed << setprecision(10) << lo << " " << sqrt(f(lo)) << "\n";
  }
  return 0;
}
