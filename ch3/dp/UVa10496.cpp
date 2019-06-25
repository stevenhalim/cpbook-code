// Collecting Beepers

#include <bits/stdc++.h>
using namespace std;

#define MAX_n 11

int n, dist[MAX_n][MAX_n], memo[MAX_n][1<<(MAX_n-1)]; // Karel + max 10 beepers

int tsp(int c, int mask) {           // mask stores the visited coordinates
  if (mask == (1<<n)-1) return dist[c][0];  // return trip to close the loop
  if (memo[c][mask] != -1) return memo[c][mask];
  int ans = 2000000000;
  for (int nxt = 1; nxt <= n; nxt++) // O(n) here
    if (!(mask & (1<<(nxt-1)))) // if coordinate nxt is not visited yet
      ans = min(ans, dist[c][nxt] + tsp(nxt, mask | (1<<(nxt-1))));
  return memo[c][mask] = ans;
}

int main() {
  int TC; scanf("%d", &TC);
  while (TC--) {
    int xsize, ysize; scanf("%d %d", &xsize, &ysize); // these two values are not used
    int x[11], y[11];
    scanf("%d %d", &x[0], &y[0]);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) // karel's position is at index 0
      scanf("%d %d", &x[i], &y[i]);
    for (int i = 0; i <= n; i++) // build distance table
      for (int j = 0; j <= n; j++)
        dist[i][j] = abs(x[i]-x[j]) + abs(y[i]-y[j]); // Manhattan distance
    memset(memo, -1, sizeof memo);
    printf("The shortest path has length %d\n", tsp(0, 0)); // DP-TSP
  }
  return 0;
}
