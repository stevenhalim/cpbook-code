// Collecting Beepers

#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

const int MAX_n = 11;

int dist[MAX_n][MAX_n], memo[MAX_n][1<<(MAX_n-1)]; // Karel + max 10 beepers

int dp(int u, int mask) {                        // mask = free coordinates
  if (mask == 0) return dist[u][0];              // close the loop
  int &ans = memo[u][mask];
  if (ans != -1) return ans;                     // computed before
  ans = 2000000000;
  int m = mask;
  while (m) {                                    // up to O(n)
    int two_pow_v = LSOne(m);                    // but this is fast
    int v = __builtin_ctz(two_pow_v)+1;          // offset v by +1
    ans = min(ans, dist[u][v] + dp(v, mask^two_pow_v)); // keep the min
    m -= two_pow_v;
  }
  return ans;
}

int main() {
  int TC; scanf("%d", &TC);
  while (TC--) {
    int xsize, ysize; scanf("%d %d", &xsize, &ysize); // these two values are not used
    int x[MAX_n], y[MAX_n];
    scanf("%d %d", &x[0], &y[0]);
    int n; scanf("%d", &n); ++n;                 // include Karel
    for (int i = 1; i < n; ++i)                  // Karel is at index 0
      scanf("%d %d", &x[i], &y[i]);
    for (int i = 0; i < n; ++i)                  // build distance table
      for (int j = i; j < n; ++j)
        dist[i][j] = dist[j][i] = abs(x[i]-x[j]) + abs(y[i]-y[j]); // Manhattan distance
    memset(memo, -1, sizeof memo);
    printf("%d\n", dp(0, (1<<(n-1))-1));         // DP-TSP
    // printf("The shortest path has length %d\n", dp(0, (1<<(n-1))-1)); // DP-TSP
  }
  return 0;
}
