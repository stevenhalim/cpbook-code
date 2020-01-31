// The Dragon of Loowater

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
  int n, m;
  while (scanf("%d %d", &n, &m), (n || m)) {
    vi D(n);
    vi H(m);
    for (int d = 0; d < n; ++d) scanf("%d", &D[d]);
    for (int k = 0; k < m; ++k) scanf("%d", &H[k]);
    sort(D.begin(), D.end());                        // sorting is an important
    sort(H.begin(), H.end());                        // pre-processing step
    int gold = 0, d = 0, k = 0;                      // both arrays are sorted
    while ((d < n) && (k < m)) {                     // while not done yet
      while ((k < m) && (D[d] > H[k])) ++k;          // find required knight k
      if (k == m) break;                             // loowater is doomed :S
      gold += H[k];                                  // pay this amount of gold
      ++d; ++k;                                      // next dragon & knight
    }
    if (d == n) printf("%d\n", gold);                // all dragons are chopped
    else        printf("Loowater is doomed!\n");
  }
  return 0;
}
