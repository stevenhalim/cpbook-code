// The Dragon of Loowater

#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n, m;
  while (scanf("%d %d", &n, &m), (n || m)) {
    vector<int> head(n);
    vector<int> height(m);
    for (int d = 0; d < n; ++d) scanf("%d", &head[d]);
    for (int k = 0; k < m; ++k) scanf("%d", &height[k]);
    sort(head.begin(), head.end());
    sort(height.begin(), height.end());
    int gold = 0, d = 0, k = 0;                      // both arrays are sorted
    while ((d < n) && (k < m)) {                     // while not done yet
      while ((k < m) && (head[d] > height[k])) ++k;  // find required knight k
      if (k == m) break;                             // loowater is doomed :S
      gold += height[k];                             // pay this amount of gold
      ++d; ++k;                                      // next dragon & knight
    }
    if (d == n) printf("%d\n", gold);                // all dragons are chopped
    else        printf("Loowater is doomed!\n");
  }
  return 0;
}
