/*          Forming Quiz Teams, the solution for UVa 10911 above         */
// if you have problems with this C++ code, please consult your programming
// text books first...
#include <bits/stdc++.h> // not C++ standard, but OK in programming contest
using namespace std;

// global variables is a bad software engineering practice, but OK for CP
int N, target;
double dist[20][20], memo[1<<16];      // 1<<16 = 2^16, note that max N = 8

double matching(int bitmask) {                        // DP state = bitmask
                     // we initialize `memo' with -1.0 in the main function
  if (memo[bitmask] > -0.5) return memo[bitmask]; // this has been computed
  if (bitmask == target) return 0;      // all students are already matched
  double ans = 1e9;                        // initialize with a large value
  int p1, p2;
  for (p1 = 0; p1 < 2*N; p1++)
    if (!(bitmask & (1<<p1)))
      break;                              // find the first bit that is off
  for (p2 = p1+1; p2 < 2*N; p2++)                  // then, try to match p1
    if (!(bitmask & (1<<p2)))       // with another bit p2 that is also off
      ans = min(ans,                                    // pick the minimum
                dist[p1][p2] + matching(bitmask | (1<<p1) | (1<<p2)));
  return memo[bitmask] = ans;    // store result in a memo table and return
}

int main() {
#ifndef ONLINE_JUDGE     // this definition is specific to UVa online judge
  freopen("in.txt", "r", stdin);            // redirect input file to stdin
#endif
  int caseNo = 1, x[20], y[20];
  while (scanf("%d", &N), N) {                    // yes, we can do this :)
    for (int i = 0; i < 2*N; i++)
      scanf("%*s %d %d", &x[i], &y[i]);                // '%*s' skips names
    for (int i = 0; i < 2*N-1; i++)        // build pairwise distance table
      for (int j = i+1; j < 2*N; j++)      // have you used `hypot' before?
        dist[i][j] = dist[j][i] = hypot(x[i]-x[j], y[i]-y[j]);
    // use DP to solve min weighted perfect matching on small general graph
    for (int i = 0; i < (1<<16); i++) memo[i] = -1.0;    // set -1.0 to all
    target = (1<<(2*N)) - 1;         // store this value as global variable
    printf("Case %d: %.2lf\n", caseNo++, matching(0));
  }
  return 0;
}
