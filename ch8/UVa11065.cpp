// Gentlemen Agreement

#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 62;

#define LSOne(S) ((S) & -(S))                    // important speedup

typedef long long ll;

ll AM[MAX_V];
int V, numIS, MIS;

void backtrack(int u, ll mask, int depth) {
  if (mask == 0) {                               // all have been visited
    ++numIS;                                     // one more possible IS
    MIS = max(MIS, depth);                       // size of the set
  }
  else {
    ll m = mask;
    while (m) {
      ll two_pow_v = LSOne(m);
      int v = __builtin_ctzl(two_pow_v);         // v is not yet used
      m -= two_pow_v;
      if (v < u) continue;                       // do not double count
      backtrack(v+1, mask & ~AM[v], depth+1);    // use v + its neighbors
    }
  }
}

int main() {
  int TC; scanf("%d", &TC);
  while (TC--) {
    int E; scanf("%d %d", &V, &E);
    // compact AM for faster set operations
    for (int u = 0; u < V; ++u)
      AM[u] = (1LL<<u);                          // u to itself
    while (E--) {
      int a, b; scanf("%d %d", &a, &b);
      AM[a] |= (1LL<<b);
      AM[b] |= (1LL<<a);
    }
    numIS = MIS = 0;
    backtrack(0, (1LL<<V)-1, 0);                 // backtracking + bitmask
    printf("%d\n", numIS);
    printf("%d\n", MIS);
  }
  return 0;
}
