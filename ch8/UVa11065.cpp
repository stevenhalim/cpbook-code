// Gentlemen Agreement

#include <bits/stdc++.>
using namespace std;

#define FOR(i,a,b) for (int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for (int i=(a),_b=(b); i>=_b; i--)
#define REP(i,n) for (int i=0,_n=(n); i<_n; i++)
#define MAXI 62

long long AM[MAXI], p2[MAXI], dpcon[MAXI];
int V, E, nS, mxS;

void backtracking(int i, long long used, int depth) {
  if (used == (1<<V)-1) {                  // all intersection are visited
    nS++;                                         // one more possible set
    mxS = max(mxS, depth);                              // size of the set
  }
  else {
    for (int j = i; j < V; j++)
      if (!(used & p2[j])) // if intesection i is not yet used
        backtracking(j+1, used|AM[j], depth+1); // use it now, and all other intersections linked to i
  }
}

int main() {
  // small speed up, pre-compute powers of 2
  p2[0] = 1;
  FOR (i, 1, MAXI) p2[i] = 2 * p2[i-1];

  int TC; scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &V, &E);

    // a more powerful, bit-wise adjacency list (for faster set operations)
    for (int i = 0; i < V; i++)
      AM[i] = (1 << i);                                  // i to itself
    for (int i = 0; i < E; i++) {
      int a, b; scanf("%d %d", &a, &b);
      AM[a] |= (1<<b);
      AM[b] |= (1<<a);
    }

    // speed up
    dpcon[V] = 0;
    FORD (i, V-1, 0) dpcon[i] = AM[i] | dpcon[i + 1];

    nS = mxS = 0;
    backtracking(0, 0, 0); // just a backtracking with bitmask/subset
    printf("%d\n%d\n", nS, mxS);
  }
  return 0;
}
