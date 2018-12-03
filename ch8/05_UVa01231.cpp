// ACORN, UVa 1231, LA 4106

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
  int i, j, c, t, h, f, a, n, acorn[2010][2010], dp[2010];

  scanf("%d", &c);
  while (c--) {
    scanf("%d %d %d", &t, &h, &f);
    memset(acorn, 0, sizeof acorn);
    for (i = 0; i < t; i++) {
      scanf("%d", &a);
      for (j = 0; j < a; j++) {
        scanf("%d", &n);
        acorn[i][n]++; // there is an acorn here
      }
    }

    for (int tree = 0; tree < t; tree++) // initialization
      dp[h] = max(dp[h], acorn[tree][h]);
    for (int height = h - 1; height >= 0; height--)
      for (int tree = 0; tree < t; tree++) {
        acorn[tree][height] +=
          max(acorn[tree][height + 1], // from this tree, +1 above
          ((height + f <= h) ? dp[height + f] : 0)); // best from tree at height + f
        dp[height] = max(dp[height], acorn[tree][height]); // update this too
      }
    printf("%d\n", dp[0]); // solution will be here
  }
  // ignore the last number 0

  return 0;
}
