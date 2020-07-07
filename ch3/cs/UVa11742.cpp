// Social Constraints 

#include <bits/stdc++.h>
using namespace std;

const int MAX_n = 8;
const int MAX_m = 20;

int main() {
  int n, m;
  while (scanf("%d %d", &n, &m), (n || m)) {
    int a[MAX_m], b[MAX_m], c[MAX_m];
    for (int j = 0; j < m; ++j)
      scanf("%d %d %d", &a[j], &b[j], &c[j]);
    int p[MAX_n];
    for (int i = 0; i < n; ++i)
      p[i] = i;
    int ans = 0;
    do { // try all possible O(n!) permutations, the largest nput 8! = 40320
      // check the given social constraints based on 'p' in O(m)
      bool all_ok = true;
      for (int j = 0; (j < m) && all_ok; ++j) { // check all constraints, max 20, each check 8 = 160
        int pos_a = p[a[j]], pos_b = p[b[j]];
        int d_pos = abs(pos_a-pos_b);
        if (c[j] > 0)
          all_ok = (d_pos <= c[j]);      // positive, at most  c[j]
        else
          all_ok = (d_pos >= abs(c[j])); // negative, at least c[j]
      }
      if (all_ok) ++ans; // all constraints are satisfied by this permutation
    }
    while (next_permutation(p, p+n)); // the overall time complexity is thus O(m * n!)
    printf("%d\n", ans); // overall complexity = 160 * 40320 = 6M, doable
  }
  return 0;
}
