/*          Forming Quiz Teams, the solution for UVa 10911 above         */
// if you have problems with this C++ code,
// please consult your programming text books first...
#include <bits/stdc++.h> // not C++ standard, but OK in programming contest
using namespace std;
// global variables is a bad software engineering practice, but OK for CP
int N, target;                                   // max N = 8
double dist[20][20], memo[1<<16];                // 1<<16 = 2^16

double matching(int mask) {                      // DP state = mask
  // we initialize `memo' with -1.0 in the main function
  if (memo[mask] > -0.5) return memo[mask];      // this has been computed
  if (mask == target) return 0;                  // all have been matched
  double ans = 1e9;                              // init with a large value
  int p1, p2;
  for (p1 = 0; p1 < 2*N; ++p1)
    if (!(mask & (1<<p1)))
      break;                                     // find the first off bit
  for (p2 = p1+1; p2 < 2*N; ++p2)                // then, try to match p1
    if (!(mask & (1<<p2)))                       // with other off bit p2
      ans = min(ans,                             // pick the minimum
                dist[p1][p2] + matching(mask | (1<<p1) | (1<<p2)));
  return memo[mask] = ans;                       // store result in a table
}

int main() {
  int caseNo = 0, x[20], y[20];
  while (scanf("%d", &N), N) {                   // yes, we can do this :)
    for (int i = 0; i < 2*N; ++i)
      scanf("%*s %d %d", &x[i], &y[i]);          // `%*s' skips names
    for (int i = 0; i < 2*N-1; ++i)              // build distance table
      for (int j = i+1; j < 2*N; ++j)            // use `hypot' function
        dist[i][j] = dist[j][i] = hypot(x[i]-x[j], y[i]-y[j]);
    for (int i = 0; i < (1<<16); ++i) memo[i] = -1.0;
    target = (1<<(2*N)) - 1;
    printf("Case %d: %.2lf\n", ++caseNo, matching(0));
  }
  return 0;
} // DP to solve min weighted perfect matching on small general graph
